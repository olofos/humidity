#ifndef PACKAGE_HANDLER_H_
#define PACKAGE_HANDLER_H_

#define PKG_VERSION 1

enum pkg_return {
    PKG_OK = 1,
    PKG_ERROR = -1,
    PKG_ERROR_NO_RETRY = -2,
};

void construct_registration_package(struct pkg_buffer *p, uint8_t node_type, uint64_t hash);
void construct_measurement_package(struct pkg_buffer *p, struct measurement *measurement);
void construct_debug_package(struct pkg_buffer *p, const struct pkg_timestamp *timestamp, const char *msg, int len);
void construct_update_request_package(struct pkg_buffer *p, uint64_t old_hash, uint64_t new_hash, uint16_t address);

int handle_ack_or_nack(struct pkg_buffer *p, struct state *state);

#endif
