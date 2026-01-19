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
    if(get_file_size(file) != 0)
    {
        printf("Failed to get file size\n");
        close_file_handler(file);
        free(file);
        exit(EXIT_FAILURE); 
    }
    if(allocate_buffer(file) != 0)
    {
        printf("Failed to allocated memory to buffer\n");
        close_file_handler(file);
        free(file);
        exit(EXIT_FAILURE);
    }
    return file;
}

int allocate_buffer(file_handler_t *file)
{
    int curr_char;
    long i = 0;
    char *buffer_aloc = malloc(sizeof(char) * file->file_size);
    if(buffer_aloc == NULL)
        return -1;
    file->buffer = buffer_aloc;
    for(int i = 0 ; i < file->file_size; i++){
        file->buffer[i] = '-';
    }
    file->buffer[file->file_size] = '\0';
    while ((curr_char = getc(file->fptr)) != EOF)
    {
        file->buffer[i] = curr_char;
        i++;
    }
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

void close_file_handler(file_handler_t *file)
{
    fclose(file->fptr);
}