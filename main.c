#include "file.h"
#include "alloc.h"
// \ //

/*
    run through spaces 
*/
void rts(char **buffer)
{
    while(**buffer == ' '){
        (*buffer)++;
    }
}

int main()
{
    file_handler_t *file = get_file_handler("program.c");
    char *new_buff = alloc_string(file->file_size);
    char *save_ptr_buffer = file->buffer;
    int fn_maybe = 0;
    int count = 0;
    printf("------------------OLD BUFF--------------------------------\n");
    printf("%s\n", file->buffer);
    printf("------------------OLD BUFF--------------------------------\n");
    while (*file->buffer != '\0'){
        char curr_char = *file->buffer;
        switch (curr_char) {
            case '(':
                fn_maybe = 1;
                new_buff[count] = curr_char;
                file->buffer++;
                count++;
                printf("'(' in i: %d\n", count);
                break;
            case ')':
                new_buff[count] = curr_char;
                file->buffer++;
                count++;
                if(fn_maybe){
                    printf("')' in i: %d\n", count);
                    rts(&file->buffer);
                    if(*file->buffer == '{'){
                        printf("TODO: NEED REMOVE, NEW LINE AND ADD\n");
                    }
                }
                break;
            default:
                new_buff[count] = curr_char;
                file->buffer++;
                count++;
        }
    }
    printf("------------------NEW BUFF--------------------------------\n");
    printf("%s\n", new_buff);
    printf("------------------NEW BUFF--------------------------------\n");
    close_file_handler(file);
    free(save_ptr_buffer);
    free(file);
    free(new_buff);
    return 0;
}