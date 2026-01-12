#include "file.h"
// \ //

int main()
{
    int getcInt;
    int currentPosBuffer = 0, lines = 0;
    file_handler_t *file = get_file_handler("program.c");
    // while ((getcInt = getc(file->fptr)) != EOF)
    // {
    //     if(currentPosBuffer == BUFFER_SIZE) {
    //         printf("buffer limit reached\n");
    //         close_file_handler(file);
    //         return 1;
    //     }
    //     if(getcInt == '\n'){
    //         currentPosBuffer = 0;
    //         printf("%s", buffer);
    //         initializeArr(buffer);
    //         lines++;
    //     }
    //     buffer[currentPosBuffer] = getcInt;
    //     currentPosBuffer++;
    // }
    close_file_handler(file);
    free(file);
    return 0;
}