#include "file.h"
#include "alloc.h"
#include "format.h"
// \ //

int main()
{
    file_handler_t *file = get_file_handler("program.c");
    /*
        TODO: realoc just if needed, crap code. 
    */ 
    char *buffer = alloc_string(file->file_size * 2);
    char *save_ptr_buffer = file->buffer;
    /*
        Format
    */
    fmt_t f = {0};
    printf("------------------OLD BUFF--------------------------------\n");
    printf("%s\n", file->buffer);
    printf("------------------OLD BUFF--------------------------------\n");
    while (*file->buffer != '\0'){
        /*
            Current char
        */
        char cc = *file->buffer;
        switch (cc) {
            case ' ':
                buffer[f.bp] = cc;
                file->buffer++;
                f.bp++;
                f.lsp++;
                break;
            case '\n':
                buffer[f.bp] = cc;
                file->buffer++;
                f.bp++;
                f.lsp = 0;
                f.l++;
                break;
            case '(':
                f.fn = 1;
                buffer[f.bp] = cc;
                file->buffer++;
                f.bp++;
                break;
            case ')':
                buffer[f.bp] = cc;
                file->buffer++;
                f.bp++;
                if(f.fn == 1){
                    rts(&file->buffer);
                    if(*file->buffer == '{'){
                        printf("line %d, pos %d: (NEW LINE, ADD line space)\n", f.l, f.bp);
                        buffer[f.bp] = '\n';
                        f.l++;
                        f.bp++;
                        if(f.lsp > 1){
                            if(f.lsp == IDS){
                                buffer[f.bp] = '\t';
                                f.bp++;
                            } else {
                                int calc = f.lsp & IDS;
                                if(calc == 0){
                                    /*
                                        pre-calc;
                                    */
                                    int pc = f.lsp/IDS;
                                    for(int i=0;i<pc;i++){
                                        buffer[f.bp] = '\t';
                                        f.bp++;
                                    }
                                } else {
                                    printf("TODO: IDENTATION, LINE SPACE: %d, %d\n", f.lsp, calc);
                                }
                            }
                        }
                        f.fn = 0;
                    }
                }
                break;
            default:
                buffer[f.bp] = cc;
                file->buffer++;
                f.bp++;
        }
    }
    write_file(OUTPUT, buffer);
    printf("------------------NEW BUFF--------------------------------\n");
    printf("%s\n", buffer);
    printf("------------------NEW BUFF--------------------------------\n");
    free(save_ptr_buffer);
    free(file);
    free(buffer);
    return 0;
}