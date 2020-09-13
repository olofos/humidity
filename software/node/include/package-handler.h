#ifndef PACKAGE_HANDLER_H_
#define PACKAGE_HANDLER_H_

void construct_registration_package(struct pkg_buffer *p, uint8_t node_type, uint64_t hash);
void construct_measurement_package(struct pkg_buffer *p, struct measurement *measurement);

#endif
