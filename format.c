#include "format.h"

/*
    run through spaces 
*/
void rts(char **buffer)
{
    while(isspace(**buffer)){
        (*buffer)++;
    }
}