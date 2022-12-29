#include <stdio.h>
#include <stdlib.h>
#include "io/file/file.h"
#include "util/util.h"

char* io_file_read_file(const char* path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		ERROR_RETURN(NULL, "Failed to read file: %s\n", path);
	}

	size_t len = 0;
	size_t allocated = IO_FILE_CHUNK_SIZE;
	char* data = (char*)malloc(allocated);
	char* tmp = NULL;
	if (data == NULL) {
		ERROR_RETURN(NULL, IO_FILE_GENERAL_MEMORY_ALLOCATION_ERROR, path);
	}

	while (!feof(file) && !ferror(file)) {
		data[len] = fgetc(file);
		len++;

		if (len >= allocated) {
			allocated += IO_FILE_CHUNK_SIZE;
			tmp = (char*)realloc(data, allocated);
			if (tmp == NULL) {
				ERROR_RETURN(NULL, IO_FILE_GENERAL_MEMORY_ALLOCATION_ERROR, path);
			}
			data = tmp;
		}
	}

	tmp = (char*)realloc(data, len);
	if (tmp == NULL) {
		ERROR_RETURN(NULL, IO_FILE_GENERAL_MEMORY_ALLOCATION_ERROR, path);
	}
	data = tmp;
	data[len - 1] = '\0';
	fclose(file);

	return data;
}