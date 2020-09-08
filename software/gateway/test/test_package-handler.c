#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "db.h"
#include "rfm69.h"
#include "package.h"
#include "package-handler.h"
#include "node.h"

#define NODE_ID 49

//////// Global variables //////////////////////////////////////////////////////

extern struct node *first_node;

// Used to work around missing CMocka functionality for testing floating point valued function parameters

double db_add_measurement__humidity;
double db_add_measurement__temperature;
double db_add_measurement__vcc;
double db_add_measurement__vmid;


//////// Mocked functions //////////////////////////////////////////////////////

time_t __wrap_time(time_t *t)
{
    return 1577934245; // 2020-01-02 03:04:05
}

int rfm69_get_rssi(void)
{
    return 100;
}

int db_register_node(uint8_t node_id, uint8_t node_type_id, uint64_t firmware_hash)
{
    check_expected(node_id);
    check_expected(node_type_id);
    check_expected(firmware_hash);
    return mock();
}

int db_add_measurement(uint8_t node_id, time_t timestamp, double humidity, double temperature, double vcc, double vmid)
{
    check_expected(node_id);
    check_expected(timestamp);

    db_add_measurement__humidity = humidity;
    db_add_measurement__temperature = temperature;
    db_add_measurement__vcc = vcc;
    db_add_measurement__vmid = vmid;

    return mock();
}

int db_add_debug_message(uint8_t node_id, time_t timestamp, char *message, int message_len)
{
    return mock();
}

int db_check_firmware_is_uptodate(uint64_t hash)
{
    return mock();
}

uint64_t db_get_latest_firmware_hash(void)
{
    return 0xBADC0FFEE;
}

struct node *node_register(uint8_t node_id, uint64_t firmware_hash, uint8_t protocol_version)
{
    static struct node node;

    node.node_id = node_id;
    node.firmware_hash = firmware_hash;
    node.protocol_version = protocol_version;
    node.next = 0;

    return &node;
}

struct node *node_get(uint8_t node_id)
{
    static struct node node;

    node.node_id = node_id;
    node.firmware_hash = 0x1212121212121212;
    node.protocol_version = 0;
    node.next = 0;

    return &node;
}


//////// Helper functions //////////////////////////////////////////////////////

#define construct_pkg(pkg) construct_pkg_helper(pkg, sizeof(pkg))

struct pkg_buffer construct_pkg_helper(uint8_t *buf, size_t len)
{
    struct pkg_buffer p;

    p.write_counter = 0;
    p.read_counter = 2;
    p.len = p.buf[0] = len + 2;
    p.from = p.buf[1] = NODE_ID;

    for(int i = 2; i < sizeof(p.buf); i++) {
        if(i - 2 < len) {
            p.buf[i] = buf[i - 2];
        } else {
            p.buf[i] = 0xAA;
        }
    }

    return p;
}

#define assert_package_equal(p,resp) do { assert_memory_equal(p.buf, resp, sizeof(resp)); assert_int_equal(p.write_counter, sizeof(resp)); } while(0)

//////// Tests /////////////////////////////////////////////////////////////////

static void test__handle_package__responds_with_nack_if_registration_fails(void **states)
{
    uint8_t pkg[] = { PKG_REGISTER, PKG_NODE_TYPE_HUMIDITY, 0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89 };
    struct pkg_buffer p = construct_pkg(pkg);

    expect_value(db_register_node, node_id, NODE_ID);
    expect_value(db_register_node, node_type_id, PKG_NODE_TYPE_HUMIDITY);
    expect_value(db_register_node, firmware_hash, 0x0123456789ABCDEF);
    will_return(db_register_node, DB_ERROR);

    handle_package(&p, sizeof(pkg));

    uint8_t resp[] = { PKG_NACK, 0x00 };

    assert_package_equal(p, resp);
}

static void test__handle_package__responds_with_set_time_if_registration_succeeds(void **states)
{
    uint8_t pkg[] = { PKG_REGISTER, PKG_NODE_TYPE_HUMIDITY, 0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89 };
    struct pkg_buffer p = construct_pkg(pkg);

    expect_value(db_register_node, node_id, NODE_ID);
    expect_value(db_register_node, node_type_id, PKG_NODE_TYPE_HUMIDITY);
    expect_value(db_register_node, firmware_hash, 0x0123456789ABCDEF);
    will_return(db_register_node, DB_OK);

    handle_package(&p, sizeof(pkg));

    // 2020-01-02 03:04:05
    uint8_t resp[] = { PKG_SET_TIME, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03 };
    assert_package_equal(p, resp);
}

static void test__handle_package__calls__db_add_measurement__with_correct_parameters(void **states)
{
    uint8_t pkg[] = { PKG_MEASUREMENT, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 0x40, 0x80, 0x20, 0x19, 0x00, 0x18, 0x44, 0x14 };
    struct pkg_buffer p = construct_pkg(pkg);

    expect_value(db_add_measurement, node_id, NODE_ID);
    expect_value(db_add_measurement, timestamp, 1577934245);

    will_return(db_add_measurement, DB_ERROR);

    handle_package(&p, sizeof(pkg));

    assert_float_equal(db_add_measurement__humidity, 50.09765625, 0.001);
    assert_float_equal(db_add_measurement__temperature, 25.125, 0.001);
    assert_float_equal(db_add_measurement__vcc, 1.5, 0.001);
    assert_float_equal(db_add_measurement__vmid, 1.2666, 0.001);
}

static void test__handle_package__responds_with_nack_if_add_measurement_fails(void **states)
{
    uint8_t pkg[] = { PKG_MEASUREMENT, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 0x40, 0x80, 0x20, 0x19, 0x00, 0x18, 0x44, 0x14 };
    struct pkg_buffer p = construct_pkg(pkg);

    expect_any(db_add_measurement, node_id);
    expect_any(db_add_measurement, timestamp);

    will_return(db_add_measurement, DB_ERROR);

    handle_package(&p, sizeof(pkg));

    uint8_t resp[] = { PKG_NACK, 0x00, };
    assert_package_equal(p, resp);
}

static void test__handle_package__responds_with_ack_if_add_measurement_succeeds(void **states)
{
    uint8_t pkg[] = { PKG_MEASUREMENT, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 0x40, 0x80, 0x20, 0x19, 0x00, 0x18, 0x44, 0x14 };
    struct pkg_buffer p = construct_pkg(pkg);

    expect_any(db_add_measurement, node_id);
    expect_any(db_add_measurement, timestamp);

    will_return(db_add_measurement, DB_OK);

    handle_package(&p, sizeof(pkg));

    uint8_t resp[] = { PKG_ACK, 0x00, };
    assert_package_equal(p, resp);
}


const struct CMUnitTest tests_for_handle_package[] = {
    cmocka_unit_test(test__handle_package__responds_with_nack_if_registration_fails),
    cmocka_unit_test(test__handle_package__responds_with_set_time_if_registration_succeeds),
    cmocka_unit_test(test__handle_package__calls__db_add_measurement__with_correct_parameters),
    cmocka_unit_test(test__handle_package__responds_with_nack_if_add_measurement_fails),
    cmocka_unit_test(test__handle_package__responds_with_ack_if_add_measurement_succeeds),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    setenv("TZ", "", 1);
    tzset();

    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_handle_package, NULL, NULL);

    return fails;
}
