#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"

char *alloc_string(long size){
    char *alloc = calloc(size + 1, 1);
    if(alloc == NULL)
        exit(EXIT_FAILURE);
    alloc[size] = '\0';
    return alloc;
}