#include <stdio.h>
#include <stdint.h>

#include "crc32.h"

int main(int argc, char *argv[])
{
    if(argc < 3) {
       fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    uint8_t buf[32768-4];
    fread(buf, sizeof(buf), 1, in);
    uint32_t crc = ~crc32(buf, sizeof(buf));
    fclose(in);

    FILE *out = fopen(argv[2], "wb");
    uint8_t out_buf[4] = {
        crc & 0x000000FF,
        (crc >> 8) & 0x000000FF,
        (crc >> 16) & 0x000000FF,
        (crc >> 24) & 0x000000FF,
    };
    fwrite(out_buf, 1, sizeof(out_buf), out);
    fclose(out);
}
