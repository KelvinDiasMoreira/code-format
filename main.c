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
                if(ctx.tlvl > 0 && *file->buffer != '}'){ 
                    rts(&file->buffer);
                    /* If we found "}" means that we need subtract 1 lvl of the three level to better identation */
                    if(*file->buffer == '}'){
                        for(int i=0;i<(ctx.tlvl - 1) * IDS; i++){
                            buffer[ctx.bp] = ' ';
                            ctx.bp++;
                        }
                    } else {
                        for(int i = 0; i < ctx.tlvl * IDS; i++){
                            buffer[ctx.bp] = ' ';
                            ctx.bp++;
                        };
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