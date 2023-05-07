#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "double_linked_list.h"

#define NAME1 "SharedMemory1"
#define NAME2 "SharedMemory2"
#define NAME3 "SharedMemory3"

#define NUM 3
#define SIZE sizeof(stList)

int main(){

    int fd1;
    int fd2;
    int fd3;
    stNode * nodePtr1;
    stNode * nodePtr2;
    stNode * nodePtr3;
    
    if((fd1 = shm_open(NAME1, O_RDONLY, 0666)) < 0){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    nodePtr1 = (stNode *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd1, 0);

    if((fd2 = shm_open(NAME2, O_RDONLY, 0666)) < 0){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    nodePtr2 = (stNode *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd2, 0);

    if((fd3 = shm_open(NAME3, O_RDONLY, 0666)) < 0){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    nodePtr3 = (stNode *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd3, 0);

    printf("Receiver mapped address1 : %p %p %p \n", nodePtr1, nodePtr1->pPrev, nodePtr1->pNext);
    printf("Receiver mapped address2 : %p %p %p \n", nodePtr2, nodePtr2->pPrev, nodePtr2->pNext);
    printf("Receiver mapped address3 : %p %p %p \n", nodePtr3, nodePtr3->pPrev, nodePtr3->pNext);

    printf("Num ID  index  Name  Number  Group\n");
    
    stNode* p = nodePtr1;

    while(p!=NULL){
        printf("%d %d %s %s %s \n",p->id, p->index, p->name, p->number, p->group);
        p = p->pNext;
    }

    munmap(nodePtr1, SIZE);
    munmap(nodePtr2, SIZE);
    munmap(nodePtr3, SIZE);

    close(fd1);
    close(fd2);
    close(fd3);

    shm_unlink(NAME1);
    shm_unlink(NAME2);
    shm_unlink(NAME3);

    return EXIT_SUCCESS;
}
