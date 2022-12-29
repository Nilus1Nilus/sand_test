#pragma once

#define IO_FILE_CHUNK_SIZE 2097152 // 2MiB
#define IO_FILE_GENERAL_MEMORY_ALLOCATION_ERROR "Failed to allocate memory for file: %s\n"

char* io_file_read_file(const char*);
char* io_file_write_file(const char*);