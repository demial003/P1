#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

void testError2();

int main()
{

    int *a = malloc(sizeof(int) * 2);
    free(a + 1);
}
