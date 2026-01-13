#include "file.h"
// \ //

int main()
{
    int getcInt;
    file_handler_t *file = get_file_handler("program.c");
    char *buffer = malloc(sizeof(char) * file->file_size);
    for(int i = 0 ; i < file->file_size; i++){
        buffer[i] = '-';
    }
    buffer[file->file_size] = '\0';
    
    int i = 0;
    if(buffer == NULL)
    {
        printf("Failed to allocated memory\n");
        close_file_handler(file);
        free(file);
        return 1;
    }
    while ((getcInt = getc(file->fptr)) != EOF)
    {
        buffer[i] = getcInt;
        i++;
    }
    printf("%s", buffer);
    close_file_handler(file);
    free(file);
    free(buffer);
    return 0;
}

// HELLS PARADISE