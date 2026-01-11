#include <stdio.h>

typedef struct FILE_HANDLER {
    FILE *fptr;
    int error;
} file_handler_t;

file_handler_t get_file_handler(char *path);
void close_handler(file_handler_t file);