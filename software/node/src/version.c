#include <stdint.h>
#include "version.h"
#include "git-version.h"

// Checksum generated during build

const char __attribute__((section(".version_info.git"))) __attribute__((used)) firmware_git_version[24] = GIT_COMMIT;
const uint32_t __attribute__((section(".version_info"))) __attribute__((used)) firmware_version = (((uint32_t) VERSION_MAJOR) << 24) | (((uint32_t) VERSION_MINOR) << 16) | VERSION_PATCH;
uint32_t __attribute__((section(".checksum"))) __attribute__((used)) firmware_crc;
