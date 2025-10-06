#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "mymalloc.h"
typedef struct
{
    int length;
    int status;
} header;

typedef struct node
{
    int data;
    struct node *next;
} Node;

int main()
{
    srand(time(NULL));

    struct timeval t0;
    struct timeval t1;
    gettimeofday(&t0, NULL);

    void *objs[120];
    void *ptrs[120];

    int flag = 0;

    int choice = 0;
    int allocations = 0;
    int idx = 0;
    while (flag < 50)
    {
        for (int i = 0; i < 120; i++)
        {
            void *p = malloc(1);
            if (p == NULL)
            {
                printf("fail");
                exit(1);
            }
            free(p);
        }
        for (int i = 0; i < 120; i++)
        {
            objs[i] = malloc(1);
        }

        for (int i = 0; i < 120; i++)
        {
            free(objs[i]);
        }

        while (allocations < 120)
        {
            choice = (rand() % 2) + 1;
            idx = rand() % 2;
            if (choice == 1)
            {
            if (ptrs[idx] != NULL)
                {
                    header *p = (header *)(ptrs[idx] - 8);
                    if (p->status == 2)
                    {
                       continue;
                    }
                }
                ptrs[idx] = malloc(1);
                allocations++;
            }
            else
            {
                if (ptrs[idx] != NULL)
                {
                    header *p = (header *)(ptrs[idx] - 8);
                    if (p->status == 2)
                    {
                        
                        free(ptrs[idx]);
                    }
                }
            }
        }

        for (int i = 0; i < 120; i++)
        {
            if (ptrs[i] != NULL)
            {
                header *p = (header *)(ptrs[i] - 8);
                if (p->status == 2)
                {
                    free(ptrs[i]);
                }

            }
        }

        Node *head = NULL;
        head = (Node *)malloc(sizeof(Node));
        head->data = 1;
        int f = 0;

        Node *cur = head;

        while (f < 85)
        {
            Node *n = (Node *)malloc(sizeof(Node));
            n->next = NULL;
            cur->next = n;
            cur = cur->next;
            f++;
        }
        f = 0;
        cur = head;
        while (cur != NULL)
        {
            Node *prev = cur;
            cur = cur->next;
            free(prev);
            f++;
        }
        flag++;
    }

    gettimeofday(&t1, NULL);
    long elapsed = (t1.tv_usec - t0.tv_usec) / 50;
    printf("Time elapsed: %ld microseconds\n", elapsed);
    return 0;
}