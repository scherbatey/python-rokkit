#include "SuperFastHash.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char * argv[])
{
    if (argc > 1) {
        size_t data_arg = argc > 2 ? 2 : 1;
        const char * data = argv[data_arg];
        const size_t len = strlen(argv[data_arg]);

        uint32_t seed;
        if (argc > 2) {
            char * end;
            seed = (uint32_t)strtoul(argv[1], &end, 10);
            if (errno != 0) {
                printf("Invalid seed value!");
                return -1;
            }
        } else
            seed = (uint32_t)len;

        uint32_t hash = SuperFastHash(data, (int)len, seed);
        printf("%u\n", hash);
    }
}
