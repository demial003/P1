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
static int initialized = 0;

int roundUp(size_t num);
void leaktest();

void initialize()
{
    for (int i = 0; i < MEMLENGTH; i++)
    {
        heap.bytes[i] = 0;
    }
    header *h = (header *)&heap.bytes[0];
    h->length = MEMLENGTH - sizeof(header);
    h->status = 0;
    atexit(leaktest);
}
void *mymalloc(size_t size, char *file, int line)
{
    if (initialized == 0)
    {
        initialize();
        initialized = 1;
    }
    int old = 0;
    char *ptr = heap.bytes;
    int sum = size + 8;
    header *h;
    while (ptr < heap.bytes + MEMLENGTH)
    {
        h = (header *)ptr;

        if (h->status == 0 && h->length >= size)
            break;

        ptr += sizeof(header) + h->length;
    }

    if (ptr >= heap.bytes + MEMLENGTH)
    {
        fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
        return NULL;
    }

    if (h->length >= size)
    {
        old = h->length;
    }
    h->length = roundUp(size);
    h->status = 2;

    header *next = (header *)((char *)(h + 1) + h->length);
    if (next <= (header *)&heap.bytes[MEMLENGTH - 16])
    {
        if (next->status != 2)
        {
            next->status = 0;
        }
        if (sum - size == 8)
        {
            next->length = MEMLENGTH - sum;
        }
        else if (old - h->length != 0)
        {
            next->length = old - h->length;
        }
    }

    return h + 1;
}

int roundUp(size_t num)
{
    if (num % 8 == 0)
        return num;
    return (num / 8 + 1) * 8;
}

void myfree(void *ptr, char *file, int line)
{
    header *h = (header *)heap.bytes;
    header *prev = NULL;
    while ((char *)h < heap.bytes + MEMLENGTH)
    {
        if ((void *)(h + 1) == ptr)
        {
            h->status = 0;
            header *next = (header *)((char *)(h + 1) + h->length);
            if ((char *)next < heap.bytes + MEMLENGTH && next->status == 0)
            {
                h->length += next->length + sizeof(header);
            }

            if (prev && prev->status == 0)
            {
                prev->length += h->length + sizeof(header);
            }
            return;
        }
        prev = h;
        h = (header *)((char *)(h + 1) + h->length);
    }
    fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
    exit(2);
}

void leaktest()
{
    int objs = 0;
    int len = 0;
    header *h = (header *)heap.bytes;

    while ((char *)h < heap.bytes + MEMLENGTH)
    {
        if (h->status == 2)
        {
            objs++;
            len += h->length;
        }
        h = (header *)((char *)(h + 1) + h->length);
    }

    if (objs > 0)
        fprintf(stderr, "mymalloc: %d bytes leaked in %d objects.\n", len, objs);
}
