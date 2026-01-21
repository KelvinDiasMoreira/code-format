#include "file.h"
#include "alloc.h"

file_handler_t *get_file_handler(char *path)
{
    file_handler_t *file = malloc(sizeof(file_handler_t));
    if(file == NULL){
        printf("Failed to allocated memory\n");
        exit(EXIT_FAILURE);
    }
    if((file->fptr = fopen(path, "rb")) == NULL){
        printf("Failed to open file\n");
        free(file);
        exit(EXIT_FAILURE);
    }
    if(get_file_size(file) != 0)
    {
        printf("Failed to get file size\n");
        goto exit; 
    }
    if(allocate_buffer(file) != 0)
    {
        printf("Failed to allocated memory to buffer\n");
        goto exit;
    }
    close_file_handler(file);
    return file;

    exit:
        close_file_handler(file);
        free(file);
        exit(EXIT_FAILURE);
}

void write_file(char *path, char *buffer)
{
    FILE *fptr;
    if((fptr = fopen(path, "w")) == NULL){
        printf("Failed to write file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fptr, buffer);
    fclose(fptr);
}

int allocate_buffer(file_handler_t *file)
{
    file->buffer = alloc_string(file->file_size);
    fread(file->buffer, 1, file->file_size, file->fptr);
    return 0;
}

int get_file_size(file_handler_t *file)
{
    // TODO: added possibility to use <sys/stat.h> if available
    if(!file || !file->fptr)
        return -1;
    if(fseek(file->fptr, 0, SEEK_END) != 0)
        return -1;
    long size = ftell(file->fptr);
    if(size < 0)
        return -1;
    if(fseek(file->fptr, 0, SEEK_SET) != 0)
        return -1;
    file->file_size = size;
    return 0;
}

void close_file_handler(const file_handler_t *file)
{
    fclose(file->fptr);
}