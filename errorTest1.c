#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

int main()
{
    // void *f = malloc(123456); this has been commented out in order to avoid unused variable error but the error /message are still correct
    int x;
    free(&x);
}
