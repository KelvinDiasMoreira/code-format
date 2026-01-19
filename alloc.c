#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"

char *alloc_string(long size){
    char *alloc = malloc(sizeof(char) * (size + 1));
    if(alloc == NULL)
        exit(EXIT_FAILURE);
    alloc[sizeof(char) * (size + 1)] = '\0';
    return alloc;
}