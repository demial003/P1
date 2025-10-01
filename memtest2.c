#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mymalloc.h"

void testCoalesce();
void testLeak();
void testErrors();
void testDeallocation();
void testThings();
int main()
{
    testThings();
    testCoalesce();
    testDeallocation();
    testLeak();
}

void testThings()
{
    void *p1 = malloc(64);
    void *p2 = malloc(48);
    void *temp = p2;
    void *p3 = malloc(40);
    free(p2);
    void *p4 = malloc(48);
    if (temp == p4)
    {
        printf("Generic test success\n");
    }
    else
    {
        printf("Generic test fail\n");
    }
    free(p1);
    free(p3);
    free(p4);
}

void testCoalesce()
{
    void *p1 = malloc(2040);
    void *p2 = malloc(2040);
    void *temp = p1;
    free(p1);
    free(p2);
    void *p3 = malloc(4080);
    if (temp == p3)
        printf("Coalesce test success\n");
    else
    {
        printf("FAIL");
    }
    free(p3);
}

void testErrors()
{

    void *f = malloc(123456);

    int x;
    free(&x);

    int *a = malloc(sizeof(int) * 2);
    free(a + 1);

    int *p = malloc(sizeof(int) * 100);
    int *q = p;
    free(p);
    free(q);
}

void testDeallocation()
{
    void *p = malloc(24);
    header *h = p - 8;
    if (h->status != 2)
        printf("Fail");
    free(p);
    if (h->status != 0)
        printf("Fail");
    else
    {
        printf("Deallocation test success\n");
    }
}
void testLeak()
{
    void *p = malloc(21);
    atexit(leaktest);
}