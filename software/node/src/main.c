#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "mcu.h"
#include "uart.h"
#include "spi-flash.h"
#include "systick.h"
#include "rfm69.h"
#include "shtc3.h"
#include "i2c.h"
#include "adc.h"
#include "rfm69-registers.h"
#include "rfm69-hal.h"
#include "rtc.h"
#include "package.h"
#include "measurement.h"
#include "pretty-print.h"
#include "aes-key.h"
#include "package-handler.h"
#include "state.h"
#include "version.h"
#include "debug.h"
#include "update.h"

#define GATEWAY_ADDRESS 0x01

#define CLEAR_SCREEN "\033[2J"

#define PERIOD_MEASUREMENT (10 * 60)
#define PERIOD_MEASUREMENT_RETRY (10)
#define PERIOD_SEND_RETRY (5)
#define SLEEP_PERIOD_MIN 1
#define MAX_RETRY 8

// Checksum generated during build

const uint32_t __attribute__((section(".version_info"))) __attribute__((used)) firmware_version = (((uint32_t) VERSION_MAJOR) << 24) | (((uint32_t) VERSION_MINOR) << 16) | VERSION_PATCH;
uint32_t __attribute__((section(".checksum"))) __attribute__((used)) firmware_crc;

#define ERROR_LOOP_PERIOD 400
#define ERROR_LOOP_MAX    10

#define ERROR_LOOP_SHTC3  2
#define ERROR_LOOP_RFM69  3
#define ERROR_LOOP_FLASH  4

static void error_loop(int n)
{
    for(;;) {
        for(int i = 0; i < n; i++) {
            ledr_on();
            delay(ERROR_LOOP_PERIOD/2);
            ledr_off();
            delay(ERROR_LOOP_PERIOD/2);
        }

        delay((ERROR_LOOP_MAX - n) * ERROR_LOOP_PERIOD);
    }
}

static void init_external_peripherals(void)
{
    i2c_init();
    shtc3_wakeup();

    uint16_t shtc3_id = shtc3_test();
    if(shtc3_id) {
        printf("SHTC3 detected (%04X)\r\n", shtc3_id);
    } else {
        printf("No SHTC3 detected\r\n");
        error_loop(ERROR_LOOP_SHTC3);
    }

    shtc3_sleep();
    i2c_deinit();

    if(rfm69_test()) {
        printf("RFM69 detected\r\n");
    } else {
        printf("No RFM69 detected\r\n");
        error_loop(ERROR_LOOP_RFM69);
    }

    rfm69_init();
    rfm69_set_aes_key(aes_key);
    rfm69_set_mode(RFM69_MODE_SLEEP);

    spi_flash_wakeup();
    if(spi_flash_test()) {
        printf("SPI Flash detected\r\n");
    } else {
        printf("No SPI Flash detected\r\n");
        error_loop(ERROR_LOOP_FLASH);
    }
    spi_flash_sleep();

    struct pkg_timestamp timestamp = {0,0,0,0,0,0};

    rtc_set_time(&timestamp);
}


static struct pkg_buffer pkg_buffer;
struct state state;

static int send_package_and_receive_reply(struct pkg_buffer *p)
{
    int ret = 0;

    rfm69_set_mode(RFM69_MODE_STANDBY);

    if(pkg_send(GATEWAY_ADDRESS, p) > 0) {
        ret = pkg_receive(p);

        if(ret <= 0) {
            printf("No reply\r\n");
        }
    } else {
        printf("Write failed\r\n");
    }

    rfm69_set_mode(RFM69_MODE_SLEEP);
    return ret;
}

static void send_measurement(void)
{
    struct measurement *measurement = measurement_get();
    if(!measurement) return;

    struct pkg_buffer *p = &pkg_buffer;

    pkg_init(p);
    construct_measurement_package(p, measurement);

    int len = send_package_and_receive_reply(p);
    int resp = PKG_ERROR;

    if(len > 0) {
        resp = handle_ack_or_nack(p);
    }

    if(resp == PKG_OK) {
        measurement_handled();
    } else if(resp == PKG_ERROR_NO_RETRY) {
        measurement_handled();
        printf("Giving up on measurement\r\n");
    } else {
        if(measurement->retries < MAX_RETRY) {
            measurement->retries++;
            state.timer.send_measurement = measurement->retries * PERIOD_SEND_RETRY;
            printf("Sending measurement failed. Trying again\r\n");
        } else {
            measurement_handled();
            printf("Giving up on measurement after %d retries\r\n", measurement->retries);
        }
    }
}

static void send_registation(void)
{
    struct pkg_buffer *p = &pkg_buffer;

    pkg_init(p);
    uint64_t hash = (((uint64_t) firmware_version) << 32) | firmware_crc;
    construct_registration_package(p, PKG_NODE_TYPE_HUMIDITY, hash);

    int len = send_package_and_receive_reply(p);
    int resp = PKG_ERROR;

    if(len > 0) {
        resp = handle_ack_or_nack(p);
    }

    if(resp != PKG_OK) {
        printf("Registration failed\r\n");
    }
}

static void send_debug(void)
{
    struct pkg_buffer *p = &pkg_buffer;

    pkg_init(p);
    struct debug_message *msg = debug_get();
    construct_debug_package(p, msg);

    int len = send_package_and_receive_reply(p);
    int resp = PKG_ERROR;

    if(len > 0) {
        resp = handle_ack_or_nack(p);
    }

    if(resp == PKG_OK) {
        debug_handled();
    } else if(resp == PKG_ERROR_NO_RETRY) {
        debug_handled();
        printf("Giving up on debug message\r\n");
    } else {
        if(msg->retries < MAX_RETRY) {
            msg->retries++;
            state.timer.send_debug = msg->retries * PERIOD_SEND_RETRY;
            printf("Sending debug message failed. Trying again\r\n");
        } else {
            debug_handled();
            printf("Giving up on debug message after %d retries\r\n", msg->retries);
        }
    }
}

int do_take_measurement(void)
{
    int measurement_failed = 0;

    printf("\r\n");

    struct measurement measurement;

    rtc_get_time(&measurement.timestamp);

    i2c_init();
    shtc3_wakeup();

    if(!shtc3_read(&measurement.humidity_temperature)) {
        measurement_failed = 1;
        printf("Reading temperature and humidity failed\r\n");
    }

    shtc3_sleep();
    i2c_deinit();

    adc_init();
    if(!adc_measure_voltages(&measurement.voltages)) {
        measurement_failed = 1;
        printf("Reading voltages failed\r\n");
    }
    adc_deinit();

    if(measurement_failed) {
        printf("Measurement failed\r\n");
        return 0;
    }

    measurement.retries = 0;

    print_measurement(&measurement);

    measurement_add(&measurement);

    return 1;
}


static void take_measurement(void)
{
    if(rtc_is_rtc_clock_initialized() && (state.timer.take_measurement == 0)) {
        if(do_take_measurement()) {
            state.timer.take_measurement = PERIOD_MEASUREMENT;
        } else {
            state.timer.take_measurement = PERIOD_MEASUREMENT_RETRY;
            debug_print("Measurement failed");
        }
    }
}

static void handle_communication(void)
{
    if(!(state.flags & STATE_FLAG_REGISTERED)) {
        send_registation();
    } else if(!measurement_empty()) {
        send_measurement();
    } else if(!debug_empty()) {
        send_debug();
    } else if(update_available()) {
    }
}

static void calculate_sleep_settings(void)
{
    uint16_t sleep_period = state.timer.take_measurement;

    if(!measurement_empty() || !debug_empty() /* || update_started() */ ) {
        state.sleep.mode = SLEEP_MODE_DEEP;
    } else {
        state.sleep.mode = SLEEP_MODE_STANDBY;
    }


    if(!(state.flags & STATE_FLAG_REGISTERED)) {
    }
    if(!measurement_empty()) {
        if(sleep_period > state.timer.send_measurement) sleep_period = state.timer.send_measurement;
    }
    if(!debug_empty()) {
        if(sleep_period > state.timer.send_debug) sleep_period = state.timer.send_measurement;
    }
    if(update_available()) {
        if(sleep_period > state.timer.send_update) sleep_period = state.timer.send_update;
    }

    if(sleep_period < SLEEP_PERIOD_MIN) {
        sleep_period = SLEEP_PERIOD_MIN;
    }

    state.sleep.period = sleep_period;
}

#define WAIT_PERIOD 200

static void wait_for_button(void)
{
    do {
        ledr_on();
        delay(WAIT_PERIOD/2);
        ledr_off();
        delay(WAIT_PERIOD/2);
    } while(button_pushed());

    printf("Push button to continue\r\n");

    do {
        ledr_on();
        delay(WAIT_PERIOD/2);
        ledr_off();
        delay(WAIT_PERIOD/2);
    } while(!button_pushed());

    do {
        ledr_on();
        delay(WAIT_PERIOD/2);
        ledr_off();
        delay(WAIT_PERIOD/2);
    } while(button_pushed());
}

#define TIMER_TICK(timer,step) do { if(timer >= step) timer -= step; else timer = 0; } while(0);

void timer_tick(void)
{
    TIMER_TICK(state.timer.take_measurement, state.sleep.period);
    TIMER_TICK(state.timer.send_measurement, state.sleep.period);
    TIMER_TICK(state.timer.send_debug, state.sleep.period);
    TIMER_TICK(state.timer.send_update, state.sleep.period);
}

int main(void)
{
    uint32_t woke_from_standby = mcu_init();

    if(!woke_from_standby) {
        printf(CLEAR_SCREEN "\r\nStarting...\r\n");
    }

    if(button_pushed()) {
        wait_for_button();
    }

    printf("\r\n");

    uint8_t conf = read_config();
    printf("Config: %d\r\n", conf);

    if(woke_from_standby) {
        state_load();
    } else {
        init_external_peripherals();
        state_init();
    }

    rfm69_set_node_address((PKG_NODE_TYPE_HUMIDITY << 6) | conf);

    for(;;) {
        ledr_on();

        take_measurement();
        handle_communication();
        calculate_sleep_settings();

        ledr_off();

        uart_deinit();
        timer_tick();
        if(state.sleep.mode == SLEEP_MODE_STANDBY) {
            state_save();
        }
        sleep(state.sleep.mode, state.sleep.period);
        uart_init_dma();
    }
}
