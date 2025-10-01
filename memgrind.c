#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "mymalloc.h"





#define SSIZE 5;

int main(){
    srand(time(NULL));

    struct timeval t0;
    struct timeval t1;
    gettimeofday(&t0, NULL);

    void * objs[120];
    void * ptrs[120];

    int flag = 0;

    int choice = 0;
    int allocations = 0;
    int idx = 0;
    while(flag < 2){
    for(int i = 0; i < 120; i++){
        void* p = malloc(1);
        if(p == NULL) {
            printf("fail");
            exit(1);
        }
        free(p);
    }

 
    for(int i = 0; i < 120; i ++){
        objs[i] = malloc(1);
       
    }

    for(int i = 0; i < 120; i++){
        free(objs[i]);
    }
    while(allocations < 120){
        choice = (rand() % 2) + 1;
        idx = rand() % 119;

        if(choice == 1){
            ptrs[idx] = malloc(1);
            allocations++;
        }
        else{
            header* p = (header*) ptrs[idx];            
        if(p != NULL && p->status == 2){
             free(p);
           }
        }
    }


    for(int i = 0; i < 120; i++){
            header* p = (header*) ptrs[idx];
            
            if(p!= NULL && p->status == 2){
                free(p);
            }     
    }


    // Node* head;
    // head->next = NULL;
    // // void *nodes[120];
    // for(int i = 0; i < 120; i++){
    //    Node* cur = head;
    //     while(cur->next){
    //         cur = cur->next;
    //     }
    //     cur->next = malloc(16);
    // }

    // Node* cur = head->next;
    // Node* prev;
    // while(cur->next){
    //     prev = cur;
    //     cur = cur-> next;
    //     free(prev);
    // }
   
    


    flag++;
    }



    
    gettimeofday(&t1, NULL);
    long elapsed = (t1.tv_usec-t0.tv_usec) / 120;
    printf("%ld\n", elapsed);
    return 0; 
    
}