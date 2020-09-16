#ifndef PACKAGE_HANDLER_H_
#define PACKAGE_HANDLER_H_

void construct_registration_package(struct pkg_buffer *p, uint8_t node_type, uint64_t hash);
void construct_measurement_package(struct pkg_buffer *p, struct measurement *measurement);
void construct_debug_package(struct pkg_buffer *p, const struct pkg_timestamp *timestamp, const char *msg);
void construct_update_request_package(struct pkg_buffer *p, uint64_t old_hash, uint64_t new_hash, uint16_t address);

#endif
