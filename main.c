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
    fmt_t ctx = {0};
    while (*file->buffer != '\0'){
        char cc = *file->buffer;
        switch (cc) {
            case '{':
                ctx.tlvl++;
                buffer[ctx.bp] = cc;
                file->buffer++;
                ctx.bp++;
                break;
            case '}':
                ctx.tlvl--;
                buffer[ctx.bp] = cc;
                file->buffer++;
                ctx.bp++;
                break;
            case '\n':
                buffer[ctx.bp] = cc;
                file->buffer++;
                ctx.bp++;
                ctx.l++;
                if(ctx.tlvl > 0){
                    int spc = 0;
                    int csp = ctx.tlvl * IDS;
                    /*
                        if ctx.tlvl = 1, the identation must be 4 spaces
                        int main()
                        { -> (ctx.tlvl = 1)
                                    (wrong)
                                    int number = 1;
                            (correct)
                            int number = 1;      
                        }
                    */
                    while (*file->buffer == ' '){
                        if(spc < csp){
                            spc++;
                            file->buffer++;
                        } 
                    }
                    /*
                        TODO: if not have enough space, must put spaces
                        int main()
                        { -> (ctx.tlvl = 1)
                            switch()
                            { -> (ctx.tlvl = 2)
                        (wrong)
                        int number = 1;
                                (correct)
                                int number = 1;
                            }
                        }  
                    */
                    /*
                        back to initial buffer position
                    */
                    while (spc > 0) {
                        spc--;
                        file->buffer--;
                    }
                }
                break;
            case '(':
                ctx.fn = 1;
                buffer[ctx.bp] = cc;
                file->buffer++;
                ctx.bp++;
                break;
            case ')':
                buffer[ctx.bp] = cc;
                file->buffer++;
                ctx.bp++;
                if(ctx.fn == 1){
                    rts(&file->buffer);
                    if(*file->buffer == '{'){
                        printf("line %d, pos %d, tree-level %d: (NEW LINE, ADD LINE SPACE)\n", ctx.l, ctx.bp, ctx.tlvl);
                        buffer[ctx.bp] = '\n';
                        ctx.l++;
                        ctx.bp++;
                        if(ctx.tlvl >= 1){
                            for(int i=0;i<ctx.tlvl*IDS;i++){
                                buffer[ctx.bp] = ' ';
                                ctx.bp++;
                            }
                        }
                        ctx.fn = 0;
                    }
                }
                break;
            default:
                /*
                    TODO: we need remove the "\r" ?
                    without this will duplicate the "/n", i don't know why
                */
                if(cc == '\r'){
                    file->buffer++;
                    break;
                }
                buffer[ctx.bp] = cc;
                file->buffer++;
                ctx.bp++;
        }
    }
    write_file(OUTPUT, buffer);
    printf("------------------HEX BUFF--------------------------------\n");
    for(long i = 0;i<file->file_size*2;i++){
        if(buffer[i] == '\n'){
            printf(" (\\n) ");
        } else if(buffer[i] == ' '){
            printf(" (S) ");
        } else {
            printf(" %0X ", buffer[i]);
        }
    }
    printf("\n");
    printf("------------------HEX BUFF--------------------------------\n");
    free(save_ptr_buffer);
    free(file);
    free(buffer);
    return 0;
}