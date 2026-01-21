/*
    Identation space
*/
#define IDS 4

typedef struct FMT {
    /*
        Buffer position
    */
    int bp;
    /*
        Line space
    */
    int lsp;
    /*
        Line
    */
    int l;
    /*
        Function
    */  
    char fn;
} fmt_t;

void rts(char **buffer);