#include <stdlib.h>
#include "wolfpack.h"

int main() {
    char *packets[] = {
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x0c\x03\x1f\x00\x00\x24\x14\x54\xdb\x60\x6f\x20\x77\x61\x79\x73\x20\x74\x6f\x20\x77\x72",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x30\x03\x1f\x00\x00\x24\x14\x54\xdb\x84\x20\x6f\x6e\x6c\x79\x20\x74\x68\x65\x20\x74\x68",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x00\x03\x1f\x00\x00\x24\x14\x54\xdb\x54\x54\x68\x65\x72\x65\x20\x61\x72\x65\x20\x74\x77",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x54\x03\x1f\x00\x00\x1f\x14\x54\xdb\xa3\x20\x50\x65\x72\x6c\x69\x73",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x18\x03\x1f\x00\x00\x24\x14\x54\xdb\x6c\x69\x74\x65\x20\x65\x72\x72\x6f\x72\x2d\x66\x72",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x24\x03\x1f\x00\x00\x24\x14\x54\xdb\x78\x65\x65\x20\x70\x72\x6f\x67\x72\x61\x6d\x73\x3b",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x48\x03\x1f\x00\x00\x24\x14\x54\xdb\x9c\x73\x2e\x20\x2d\x20\x41\x6c\x61\x6e\x20\x4a\x2e",
        "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x3c\x03\x1f\x00\x00\x24\x14\x54\xdb\x90\x69\x72\x64\x20\x6f\x6e\x65\x20\x77\x6f\x72\x6b",
    };
    unsigned int packets_len = 8;
    unsigned int message_len = 60; 
    char *message_act = malloc(message_len*sizeof(char));

    // fill memory with "random" garbage
    srand(444);
    for (unsigned int i = 0; i < message_len; i++)
        message_act[i] = (char)(rand() % 90 + 35);

    reconstruct_sf((unsigned char **)packets, packets_len, message_act, message_len);
    free(message_act);
    return 0;
}