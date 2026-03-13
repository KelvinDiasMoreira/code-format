#include <ctype.h>
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
        Tree level
    */
    int tlvl;
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