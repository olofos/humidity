#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#include "rfm69.h"
#include "rfm69-registers.h"
#include "db.h"

#define SERVER_NAME "/tmp/humidity-test-server.socket"
#define BUF_SIZE 64

static uint8_t node_address;
static int sock = -1;

static uint8_t send_buf[BUF_SIZE];
static uint8_t recv_buf[BUF_SIZE];

static int recv_len;

static uint8_t send_index;
static uint8_t recv_index;

struct sockaddr_un client_name;
socklen_t client_name_len;


static void exit_error(const char *s)
{
    perror(s);
    if(sock >= 0) {
        close(sock);
    }
    unlink(SERVER_NAME);
    db_deinit();
    exit(1);
}

void rfm69_hal_init(void)
{
    unlink(SERVER_NAME);

    sock = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (sock < 0) {
        exit_error("opening datagram socket");
    }

    struct sockaddr_un addr = {
        .sun_family = AF_UNIX,
        .sun_path = SERVER_NAME,
    };


    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr))) {
        exit_error("binding name to datagram socket");
    }

    printf("Bound socket %s\n", SERVER_NAME);
}

void rfm69_hal_deinit(void)
{
    close(sock);
    unlink(SERVER_NAME);
}

static void write_to_fifo(uint8_t val)
{
    if(send_index < BUF_SIZE) {
        send_buf[send_index++] = val;
    }
}

void rfm69_hal_write_byte(uint8_t reg, uint8_t val)
{
    switch(reg) {
    case RFM69_REG_OP_MODE:
        if(val == RFM69_MODE_RX) {
            recv_index = 0;
        }
        break;
    case RFM69_REG_NODE_ADRS:
        node_address = val;
        break;
    case RFM69_REG_FIFO:
        write_to_fifo(val);
        break;
    default:
        break;
    }
}

void rfm69_hal_write(uint8_t reg, const uint8_t *buf, uint8_t len)
{
    for(int i = 0; i < len; i++) {
        if(reg == RFM69_REG_FIFO) {
            rfm69_hal_write_byte(RFM69_REG_FIFO, buf[i]);
        } else {
            rfm69_hal_write_byte(reg + i, buf[i]);
        }
    }
}

uint8_t rfm69_hal_read_byte(uint8_t reg)
{
    switch(reg) {
    case RFM69_REG_IRQ_FLAGS1:
        return 0xFF;

    case RFM69_REG_VERSION:
        return 0x24;

    case RFM69_REG_RSSI_VALUE:
        return 100;

    case RFM69_REG_FIFO:
        if(recv_index < BUF_SIZE) {
            if(recv_index >= recv_len) {
                printf("Warning: reading outside received package (%d)\n", recv_index);
            }

            return recv_buf[recv_index++];
        }
        break;
    }
    return 0;
}

void rfm69_hal_read(uint8_t reg, uint8_t *buf, uint8_t len)
{
    for(int i = 0; i < len; i++) {
        if(reg == RFM69_REG_FIFO) {
            buf[i] = rfm69_hal_read_byte(RFM69_REG_FIFO);
        } else {
            buf[i] = rfm69_hal_read_byte(reg + i);
        }
    }
}

// Wait for interrupts (two separate functions so that we can set separate timouts)
// Returns:
//   > 0  if interrupt fired
//   = 0  if timed out
//   < 0  on error

int rfm69_wait_for_payload_ready(void)
{
    client_name_len = sizeof(client_name);
    recv_len = recvfrom(sock, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *) &client_name, &client_name_len);

    if(recv_len <= 0) {
        return recv_len;
    }

    printf("Received: ");
    for(int i = 0; i < recv_len; i++) {
        printf("%02x ", recv_buf[i]);
    }
    printf("\n");

    if(recv_len != recv_buf[0] + 1) {
        printf("Wrong package length: received %d byte but %d indicated\n", recv_len, recv_buf[0] + 1);
        return -1;
    }

    if(recv_buf[1] != node_address) {
        printf("Package is addressed to %d but I am %d\n", recv_buf[1], node_address);
        return 0;
    }

    return 1;
}

int rfm69_wait_for_packet_sent(void)
{
    printf("Sending: ");
    for(int i = 0; i < send_index; i++) {
        printf("%02x ", send_buf[i]);
    }
    printf("\n");

    sendto(sock, send_buf, send_index, 0, (const struct sockaddr *)&client_name, client_name_len);

    send_index = 0;

    return 0;
}
