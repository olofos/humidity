#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include <sys/file.h>

#include "rfm69.h"
#include "db.h"
#include "package.h"
#include "aes-key.h"
#include "package-handler.h"
#include "firmware.h"

#define LOCKNAME "/tmp/humidity-gateway.lock"

void sighandler(int);

static int done = 0;

#define GATEWAY_ADDRESS 1

static int take_lock(void)
{
    const char *lockname = LOCKNAME;
    int fd = open(lockname, O_RDONLY | O_CREAT, 0444);
    if(fd < 0) {
        perror("Could not open lock file");
        return -1;
    }
    if(flock(fd, LOCK_EX | LOCK_NB) < 0) {
        perror("Could not acquire lock");
        return -1;
    }
    return fd;
}

int main(void)
{
    struct sigaction sa = {
        .sa_handler = sighandler,
    };

    sigaction(SIGINT, &sa, 0);

    if(take_lock() < 0) {
        return 1;
    }

    // Make sure we work in UTC
    setenv("TZ", "", 1);
    tzset();

    char *db_filename = "../db/humidity.db";

    if(getenv("HUMIDITY_DB")) {
        db_filename = getenv("HUMIDITY_DB");
    } else if(getenv("DB")) {
        db_filename = getenv("DB");
    }

    printf("Opening database %s\n", db_filename);
    if(db_init(db_filename) != DB_OK) {
        fprintf(stderr, "Failed initializing database\n");
        return 1;
    }

    if(getenv("HUMIDITY_FW")) {
        if(firmware_set_dir(getenv("HUMIDITY_FW")) < 0) {
            fprintf(stderr, "Could not set firmware dir\n");
            goto err;
        }

    } else if(firmware_set_dir_from_file(db_filename) < 0) {
        fprintf(stderr, "Could not set firmware dir\n");
        goto err;
    }

    rfm69_init();
    rfm69_set_node_address(GATEWAY_ADDRESS);
    rfm69_set_aes_key(aes_key);

    uint8_t rfm69_version = rfm69_get_version();

    printf("RFM69 Version: %02X\r\n", rfm69_version);

    struct pkg_buffer pkg_buffer;

    while(!done) {
        struct pkg_buffer *p = &pkg_buffer;
        pkg_init(p);

        int len = pkg_receive(p);

        if(done) break;

        if(len > 0) {
            handle_package(p, len);
            pkg_send(p->from, p);
        } else {
            printf(".");
            fflush(stdout);
        }
    }

    printf("Quitting\n");

    rfm69_deinit();
    firmware_deinit();
    db_deinit();

    return 0;

err:
    rfm69_deinit();
    firmware_deinit();
    db_deinit();

    return 1;
}


void sighandler(int s)
{
    printf("Caught signal: %d\n", s);
    done = 1;
}
