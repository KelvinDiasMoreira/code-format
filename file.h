#include <stdio.h>
#include <stdlib.h>

#define OUTPUT "output.c"

typedef struct FILE_HANDLER {
    char *buffer;
    FILE *fptr;
    long file_size;
} file_handler_t;

file_handler_t *get_file_handler(char *path);
void write_file(char *path, char *buffer, int size);
int allocate_buffer(file_handler_t *file);
int get_file_size(file_handler_t *file);