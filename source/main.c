#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"

void print_usage(const char *program_name) {
    fprintf(stdout, "Usage: %s  <ROM file>  <file to insert>  <offset (hex)>\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    uint8_t *rom = read_file_into_memory(argv[1]);
    uint32_t rom_length = get_unopened_file_size(argv[1]);

    uint8_t *file_to_insert = read_file_into_memory(argv[2]);
    uint32_t file_to_insert_length = get_unopened_file_size(argv[2]);

    uint32_t offset = strtoul(argv[3], NULL, 16);

    // Check to make sure we don't write out of bounds
    if (offset + file_to_insert_length > rom_length) {
        fprintf(stderr, "Cannot insert file %s at offset 0x%X: File contents would go past end of ROM\n", argv[2], offset);
        free(rom);
        free(file_to_insert);
        return EXIT_FAILURE;
    }

    memcpy(&rom[offset], file_to_insert, file_to_insert_length);
    write_file_to_disk(rom, rom_length, argv[1]);

    free(rom);
    free(file_to_insert);

    return EXIT_SUCCESS;
}
