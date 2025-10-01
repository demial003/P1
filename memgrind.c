#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "mymalloc.h"

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
            idx = rand() % 119;

            if (choice == 1)
            {
                ptrs[idx] = malloc(1);
                allocations++;
            }
            else
            {
                header *p = (header *)ptrs[idx];
                if (p != NULL && p->status == 2)
                {
                    free(p);
                }
            }
        }
        for (int i = 0; i < 120; i++)
        {
            header *p = (header *)ptrs[idx];

            if (p != NULL && p->status == 2)
            {
                free(p);
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

        Node *head2 = NULL;
        head2 = (Node *)malloc(sizeof(Node));
        head2->data = 1;
        Node *cur2 = head;
        int f2 = 0;
        while (f2 < 85)
        {
            Node *n2 = (Node *)malloc(sizeof(Node));
            n2->next = NULL;
            cur2->next = n2;
            cur2 = cur2->next;
            f2++;
        }
        Node *prev2 = head;
        Node *node = head->next;

        while (prev2 != NULL && node != NULL)
        {
            prev2->next = node->next;
            free(node);
            prev2 = prev2->next;
            if (prev2 != NULL)
                node = prev2->next;
        }
        node = head;
        f2 = 0;
        while (node != NULL)
        {
            Node *prev2 = node;
            node = node->next;
            free(prev2);
            f2++;
        }
        flag++;
    }

    gettimeofday(&t1, NULL);
    long elapsed = (t1.tv_usec - t0.tv_usec) / 50;
    printf("Time elapsed: %ld microseconds\n", elapsed);
    return 0;
}