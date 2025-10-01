#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 4096
static union
{
    char bytes[MEMLENGTH];
    double not_used;
} heap;

int roundUp(size_t num);
void *mymalloc(size_t size, char *file, int line)
{
    int valid = 1;
    int old = 0;
    header *p = (header *)&heap.bytes[0];
    int sum = size + 8;
    while (p < (header *)&heap.bytes[MEMLENGTH - 1])
    {
        if (p->status == 0)
        {
            if (p->length != 0 && p->length < size)
            {
                p += p->length / 8 + 1;
                continue;
            }
            else
            {
                valid = 2;
                break;
            }
        }

        sum += p->length;
        if (sum > MEMLENGTH)
        {
            printf("%d\n", sum);
            printf("malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
            return NULL;
        }

        p += p->length / 8 + 1;
    };

    if (valid == 1)
    {
        printf("malloc: Unable to allocate %zu bytessss (%s:%d)\n", size, file, line);
        return NULL;
    }

    if (p->length >= size)
    {
        old = p->length;
    }
    p->length = roundUp(size);
    p->status = 2;

    header *next = p + p->length / 8 + 1;
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
        else if (old - p->length != 0)
        {
            next->length = old - p->length;
        }
    }

    return p + 1;
}

int roundUp(size_t num)
{
    if (num % 8 == 0)
        return num;
    return (num / 8 + 1) * 8;
}

void myfree(void *ptr, char *file, int line)
{
    void *p0 = &heap.bytes[0];
    int there = 0;
    while (p0 != &heap.bytes[MEMLENGTH - 1])
    {
        if (ptr == p0)
        {
            there = 1;
            break;
        }
        else
        {
            ++p0;
        }
    }
    if (there == 0)
    {
        printf("Inappropriate ppointer (%s:%d)\n", file, line);
        exit(2);
    }

    header *p = ptr - 8;

    if (p->status == 2)
    {
        p->status = 0;
    }
    else
    {
        printf("Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    header *cur = (header *)&heap.bytes[0];
    header *h = (header *)&heap.bytes[0];

    int sum = 8;
    while (cur < (header *)&heap.bytes[MEMLENGTH - 32])
    {

        sum += cur->length;
        if (cur->status == 0 && sum != MEMLENGTH)
        {
            header *next = cur + cur->length / 8 + 1;
            if (next > (header *)&heap.bytes[MEMLENGTH - 32])
                break;

            if (next->status == 0)
            {
                cur->length += next->length + 8;
            }
        }
        cur += cur->length / 8 + 1;
    };
    header *n = h + h->length / 8 + 1;
    if (h->length < 4088 && h->status == 0 && n->status == 0)
    {
        h->length += n->length;
    }
}

void leaktest()
{

    int objs = 0;
    int len = 0;

    for (int i = 0; i < MEMLENGTH - 16; i++)
    {
        header *p = (header *)&heap.bytes[i];
        if (p->status == 2)
        {
            objs++;
            len += p->length;
        }
    }

    if (objs != 0 && len != 0)
    {
        printf("mymalloc: %d bytes leaked in %d objects.\n", len, objs);
    }
}
