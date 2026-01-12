#include "file.h"

file_handler_t *get_file_handler(char *path)
{
    file_handler_t *file = malloc(sizeof(file_handler_t));
    if(file == NULL){
        printf("Failed to allocated memory\n");
        exit(1);
    }
    if((file->fptr = fopen(path, "r+")) == NULL){
        printf("Failed to open file\n");
        free(file);
        exit(EXIT_FAILURE);
    }
    get_file_size(file);
    return file;
}

void get_file_size(file_handler_t *file)
{
    fseek(file->fptr, 0, SEEK_END);
    file->file_size = ftell(file->fptr);
    fseek(file->fptr, 0, SEEK_SET);
}

void close_file_handler(file_handler_t *file)
{
    fclose(file->fptr);
}