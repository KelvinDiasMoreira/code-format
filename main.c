#include "file.h"
// \ //

int main()
{
    file_handler_t *file = get_file_handler("program.c");    
    printf("%s", file->buffer);
    close_file_handler(file);
    free(file->buffer);
    free(file);
    return 0;
}