#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

int main()
{

    int *p = malloc(sizeof(int) * 100);
    int *q = p;
    free(p);
    free(q);
}
