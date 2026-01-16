#include "file.h"
// \ //

int main()
{
    int getcInt;
    file_handler_t *file = get_file_handler("program.c");    
    int i = 0;
    while ((getcInt = getc(file->fptr)) != EOF)
    {
        file->buffer[i] = getcInt;
        i++;
    }
    printf("%s", file->buffer);
    close_file_handler(file);
    free(file->buffer);
    free(file);
    return 0;
}