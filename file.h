#include <stdio.h>
#include <stdlib.h>

typedef struct FILE_HANDLER {
    char *buffer;
    FILE *fptr;
    long file_size;
} file_handler_t;

file_handler_t *get_file_handler(char *path);
int allocate_buffer(file_handler_t *file);
void init_buffer(file_handler_t *file);
int get_file_size(file_handler_t *file);
void close_file_handler(file_handler_t *file);