#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 4096
static union
{
    char bytes[MEMLENGTH];
    double not_used;
} heap;

typedef struct
{
    int length;
    int status;
} header;
int roundUp(size_t num);
void *mymalloc(size_t size, char *file, int line)
{
    header *p = (header *)&heap.bytes[0];
    int sum = size + 8;
    while (p->status == 2)
    {
        sum += p->length;
        if (sum > MEMLENGTH)
        {
            printf("malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
            return NULL;
        }
        p += p->length / 8 + 1;
    };

    
    p->length = roundUp(size);
    p->status = 2;



    return p + 1;

}

int roundUp(size_t num)
{
    if (num % 8 == 0) 
        return num;
    return (num / 8 + 1) * 8;
}

void myfree(void *ptr, char *file, int line){
    void * p0 = &heap.bytes[0];
    int there = 0;
    while(p0 != &heap.bytes[MEMLENGTH - 1]){
        if(ptr == p0) {
            there = 1;
            break;
        }
        else{
            ++p0;
        }
    }
    if(there == 0) {
        printf("Inappropriate ppointer (%s:%d)\n", file, line);
        exit(2);
    }

    header* p = ptr - 8;

    if(p->status == 2) {
        p->status = 0;
    }
    else{
    printf("%p\n", p);
    printf("%d\n", p->status);
        printf("Inappropriate ppointer (%s:%d)\n", file, line);
        exit(2);
    }
}

void leaktest(){
    
    int objs = 0;
    int len = 0;

    for(int i = 0; i < MEMLENGTH - 16; i++){
        header *p = (header*) &heap.bytes[i];
        if(p->status == 2){
            objs++;
            len+= p->length;
        }
    }

    if(objs != 0 && len != 0){
        printf("mymalloc: %d bytes leaked in %d objects.\n", len, objs);
    }

    
}
