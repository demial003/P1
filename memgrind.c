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


int main(){
    srand(time(NULL));

    struct timeval t0;
    struct timeval t1;
    gettimeofday(&t0, NULL);

    char * objs[120];
    void * ptrs[120];

    int flag = 0;

    int choice = 0;
    int allocations = 0;
    int idx = 0;
    while(flag < 50){
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
    for(int i = 0; i < 120; i ++){
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
           if(p != NULL){
             free(p);
           }
        }
    }


    for(int i = 0; i < 120; i++){
            header* p = (header*) ptrs[idx];
            if(p!= NULL){
                free(p);
            }     
    }


    

    flag++;
    }



    
    gettimeofday(&t1, NULL);
    long elapsed = (t1.tv_usec-t0.tv_usec) / 120;
    printf("%ld\n", elapsed);
    return 0; 
    
}