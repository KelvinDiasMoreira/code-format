#include <stdio.h>
#include <stdlib.h>

typedef struct FILE_HANDLER {
    FILE *fptr;
    long file_size;
} file_handler_t;

file_handler_t *get_file_handler(char *path);
void get_file_size(file_handler_t *file);
void close_file_handler(file_handler_t *file);