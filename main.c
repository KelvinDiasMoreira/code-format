#include "file.h"
// \ //
#define IN 1
#define OUT 0
#define BUFFER_SIZE 50

void initializeArr(char arr[BUFFER_SIZE])
{
    for(int i = 0; i < BUFFER_SIZE; i++)
        arr[i] = '-';
    arr[BUFFER_SIZE] = '\0';
}

int main()
{
    int getcInt;
    char buffer[BUFFER_SIZE];
    int currentPosBuffer = 0, lines = 0;
    initializeArr(buffer);
    file_handler_t file = get_file_handler("program.c");
    if(file.error)
    {
        printf("Failed to open file\n");
        close_handler(file);
        return 1;
    }
    while ((getcInt = getc(file.fptr)) != EOF)
    {
        if(currentPosBuffer == BUFFER_SIZE) {
            printf("buffer limit reached\n");
            close_handler(file);
            return 1;
        }
        if(getcInt == '\n'){
            currentPosBuffer = 0;
            printf("%s\n", buffer);
            initializeArr(buffer);
            lines++;
        }
        buffer[currentPosBuffer] = getcInt;
        currentPosBuffer++;
    }
    close_handler(file);
    return 0;
}