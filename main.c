#include "file.h"
// \ //

int main()
{
    file_handler_t *file = get_file_handler("program.c");
    printf("--------------------------------------------------\n");
    printf("%s\n", file->buffer);
    printf("--------------------------------------------------\n");
    int fn_maybe = 0;
    for(long i = 0; i < file->file_size; i++){
        // printf("%c\n", file->buffer[i]);
        char curr_char = file->buffer[i];
        if(curr_char == '('){
            fn_maybe = 1;
            printf("'(' in i: %ld\n", i);
        } else if (curr_char == ')' && fn_maybe){
            printf("')' in i: %ld\n", i);
        }
    }
    printf("%d", fn_maybe);
    close_file_handler(file);
    free(file->buffer);
    free(file);
    return 0;
}