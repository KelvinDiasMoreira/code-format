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
    /*
        Inside a switch statement ?
    */
    int swt;
} fmt_t;

void rts(char **buffer);