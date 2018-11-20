#include "rokkit_hash.h"
#include "stdio.h"
#include "SuperFastHash.h"

int main(int argc, char * argv[])
{
    if (argc == 2) {
        uint32_t hash = rokkit_hash(argv[1], strlen(argv[1]));
        printf("%u\n", hash);
        hash = SuperFastHash(argv[1], strlen(argv[1]), 0);
        printf("%u\n", hash);
    }
}
