#include <string.h>
#include "file.h"
#include "alloc.h"
#include "format.h"

void is_switch(char *b, fmt_t *ctx)
{
    /* shit code ahead  */
    int ipos = ctx->bp - 1;
    /* if "switch ()" dont will work....
       need fix, but not now
    */
    while(b[ipos] != ' '){
        ipos--;
    }
    /* maybe is a "switch" -> 6 */
    if(((ctx->bp - 1) - (ipos + 1)) == 6){
        char *tstr = alloc_string(sizeof(char) * 6);
        int tstrc = 0;
        for(int i = ipos + 1; i < ctx->bp - 1; i++){
            tstr[tstrc] = b[i];
            tstrc++;
        }
        tstr[tstrc + 1] = '\0';
        if(strcmp(tstr, "switch") == 0){
            ctx->swt = 1;
        }
        free(tstr);
    }
}

/*
    Move buffer and file buffer
*/
void mbfb(char c, file_handler_t *f, fmt_t *ctx, char *b)
{
    b[ctx->bp] = c;
    f->buffer++;
    ctx->bp++;
}

int main()
{
    file_handler_t *file = get_file_handler("program.c");
    /*
        TODO: realoc just if needed, crap code. 
    */ 
    char *buffer = alloc_string(file->file_size * 2);
    fmt_t ctx = {0};
    while (*file->buffer != '\0'){
        char cc = *file->buffer;
        switch (cc) {
            case '{':
                ctx.tlvl++;
                mbfb(cc, file, &ctx, buffer);
                break;
            case '}':
                ctx.tlvl--;
                mbfb(cc, file, &ctx, buffer);
                break;
            case '\n':
                mbfb(cc, file, &ctx, buffer);
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
                mbfb(cc, file, &ctx, buffer);
                is_switch(buffer, &ctx);
                break;
            case ')':
                mbfb(cc, file, &ctx, buffer);
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
                mbfb(cc, file, &ctx, buffer);
        }
    }
    write_file(OUTPUT, buffer, ctx.bp);
    printf("------------------STR BUFF--------------------------------\n");
    printf("%s", buffer);
    printf("\n");
    printf("------------------STR BUFF--------------------------------\n");
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
    return 0;
}