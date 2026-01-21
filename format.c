#include "format.h"

/*
    run through spaces 
*/
void rts(char **buffer)
{
    while(**buffer == ' '){
        (*buffer)++;
    }
}