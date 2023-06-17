#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "double_linked_list.h"

#define NAME "SharedMemory"
#define NUM 3
#define SIZE sizeof(stList)

int main(){
    int fd;
    if((fd = shm_open(NAME, O_RDONLY, 0666)) < 0){
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    stNode * nodePtr;
    stList * ListPtr;
    ListPtr = (stList *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("receiver mapped address : %p\n", nodePtr);

    printf("ID  index  Name  Number  Group\n");
    
    stNode* p;
    p = ListPtr->pHead;

    while(p!=NULL){
        printf("%d %d %s %s %s \n", p->id, p->index, p->name, p->number, p->group);
        p = p->pNext;
    }
    /*
    for(int i=0; i<1 ; i++){
        printf("%d %d %s %s %s \n", nodePtr[i].id, nodePtr[i].index, nodePtr[i].name, nodePtr[i].number, nodePtr[i].group);
    }
    */

    munmap(nodePtr, SIZE);
    close(fd);
    shm_unlink(NAME);

    return EXIT_SUCCESS;
}
