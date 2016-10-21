#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void print_usage(const char *program_name) {
    fprintf(stdout, "Usage: %s /path/to/ROM /path/to/file/to/insert <offset (hex)>\n", program_name);
}

size_t get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    assert(size > 0);
    rewind(file);
    return size;
}

size_t get_unopened_file_size(const char *filename) {
    FILE *file_handle = fopen(filename, "rb");
    assert(file_handle != NULL);
    
    size_t file_size = get_file_size(file_handle);

    int close_success = fclose(file_handle);
    assert(close_success == 0);

    return file_size;
}

uint8_t *read_file_into_memory(const char *filename) {
    FILE *file_handle = fopen(filename, "rb");
    assert(file_handle != NULL);
    
    size_t file_size = get_file_size(file_handle);
    uint8_t *file_buffer = calloc(file_size, sizeof(uint8_t));
    assert(file_buffer != NULL);

    size_t items_read = fread(file_buffer, sizeof(uint8_t), file_size, file_handle);
    assert(items_read == file_size*sizeof(uint8_t));

    int close_success = fclose(file_handle);
    assert(close_success == 0);

    return file_buffer;
}

void write_file_to_disk(const uint8_t *data, uint32_t length, const char *filename) {
    FILE *file_handle = fopen(filename, "wb");
    assert(file_handle != NULL);

    size_t items_written = fwrite(data, sizeof(uint8_t), length, file_handle);
    assert(items_written == length*sizeof(uint8_t));

    int close_success = fclose(file_handle);
    assert(close_success == 0);
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
