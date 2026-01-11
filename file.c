#include "file.h"

file_handler_t get_file_handler(char *path)
{
    file_handler_t file = {0};
    if((file.fptr = fopen(path, "r+")) == NULL){
        file.error = 1;
    }
    printf("path >>> %s\n", path);
    printf("ptr to file >>> %p\n", file.fptr);
    return file;
}

void close_handler(file_handler_t file)
{
    printf("closing handler ptr >>> %p, with error >>> %d\n", file.fptr, file.error);
    fclose(file.fptr);
}