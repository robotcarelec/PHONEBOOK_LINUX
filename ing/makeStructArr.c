#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "double_linked_list.h"


#define NAME "SharedMemory"
#define NUM 2
#define SIZE sizeof(stNode)

void AddNewNodeSample (stList* ListPtr);

int main(){
    int fd; 
    if ((fd = shm_open(NAME, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    
    ftruncate(fd, NUM*SIZE);
    
    stNode *nodePtr;

    nodePtr = (stNode *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    printf("sender mapped address : %p\n", nodePtr);

    nodePtr[0].id = 10001;
    nodePtr[0].index = 1;
    strcpy(nodePtr[0].name, "KIM CheolMin");
    strcpy(nodePtr[0].number, "010-5324.2342");
    strcpy(nodePtr[0].group, "Team");
    nodePtr[0].pPrev = NULL;
    nodePtr[0].pNext = NULL;

    nodePtr[1].id = 10002;
    nodePtr[1].index = 2;
    strcpy(nodePtr[1].name, "YI TAE  YOUB");
    strcpy(nodePtr[1].number, "010-8560.3900");
    strcpy(nodePtr[1].group, "Domain");
    nodePtr[1].pPrev = NULL;
    nodePtr[1].pNext = NULL;
    
    printf("ID  index  Name  Number  Group\n");
    int i;
    for(i=0;i<NUM;i++){
        //printf("[%d]\n",i);
        printf("%d %d %s %s %s\n",nodePtr[i].id, nodePtr[i].index, nodePtr[i].name, nodePtr[i].number, nodePtr[i].group);
    }

/*
    
*/

    munmap(nodePtr, SIZE);

    close(fd);
    
    return EXIT_SUCCESS;
}
