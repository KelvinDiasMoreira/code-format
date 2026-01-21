#include "file.h"
#include "alloc.h"
#include "format.h"
// \ //

int main()
{
    file_handler_t *file = get_file_handler("program.c");
    char *new_buff = alloc_string(file->file_size * 2);
    char *save_ptr_buffer = file->buffer;
    /*
        Format
    */
    fmt_t f = {0};
    printf("------------------OLD BUFF--------------------------------\n");
    printf("%s\n", file->buffer);
    printf("------------------OLD BUFF--------------------------------\n");
    while (*file->buffer != '\0'){
        char curr_char = *file->buffer;
        switch (curr_char) {
            case ' ':
                new_buff[f.bp] = curr_char;
                file->buffer++;
                f.bp++;
                f.lsp++;
                break;
            case '\n':
                new_buff[f.bp] = curr_char;
                file->buffer++;
                f.bp++;
                f.lsp = 0;
                f.l++;
                break;
            case '(':
                f.fn = 1;
                new_buff[f.bp] = curr_char;
                file->buffer++;
                f.bp++;
                break;
            case ')':
                new_buff[f.bp] = curr_char;
                file->buffer++;
                f.bp++;
                if(f.fn == 1){
                    rts(&file->buffer);
                    if(*file->buffer == '{'){
                        printf("line %d, pos %d: (NEW LINE, ADD line space)\n", f.l, f.bp);
                        new_buff[f.bp] = '\n';
                        f.l++;
                        f.bp++;
                        if(f.lsp > 1){
                            /*
                                TODO: refactor to use "\t" cause imagine that we have 8 of line space
                                if we use "' '" wee need 8 byte, but if we use "\t" its just 1 byte.
                                make sense ?
                            */
                            // for(int i = 0 ; i < f.lsp ; i++){
                                // new_buff[f.bp] = ' ';
                                // f.bp++;
                            // }
                            if(f.lsp == 4){
                                new_buff[f.bp] = '\t';
                                f.bp++;
                            } else {
                                int calc = f.lsp & 4;
                                if(calc == 0){
                                    for(int i=0;i<(f.lsp/4);i++){
                                        new_buff[f.bp] = '\t';
                                        f.bp++;
                                    }
                                }
                                printf("TODO: IDENTATION, LINE SPACE: %d, %d\n", f.lsp, calc);
                            }
                        }
                        f.fn = 0;
                    }
                }
                break;
            default:
                new_buff[f.bp] = curr_char;
                file->buffer++;
                f.bp++;
        }
    }
    write_file(OUTPUT, new_buff);
    printf("------------------NEW BUFF--------------------------------\n");
    printf("%s\n", new_buff);
    printf("------------------NEW BUFF--------------------------------\n");
    free(save_ptr_buffer);
    free(file);
    free(new_buff);
    return 0;
}