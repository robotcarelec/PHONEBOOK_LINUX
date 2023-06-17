#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "double_linked_list.h"


#define NAME1 "SharedMemory1"
#define NAME2 "SharedMemory2"
#define NAME3 "SharedMemory3"

#define NUM 3
#define SIZE sizeof(stList)

//void AddNewNodeSample (stList* ListPtr);

int main(){
    int fd1; 
    int fd2;
    int fd3;
    stNode *nodePtr1;
    stNode *nodePtr2;
    stNode *nodePtr3;

    if ((fd1 = shm_open(NAME1, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }    
    ftruncate(fd1, SIZE);        
    nodePtr1 = (stNode *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    printf("sender mapped address1 : %p\n", nodePtr1);

    if ((fd2 = shm_open(NAME2, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }    
    ftruncate(fd2, SIZE);        
    nodePtr2 = (stNode *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    printf("sender mapped address2 : %p\n", nodePtr2);

    if ((fd3 = shm_open(NAME3, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }    
    ftruncate(fd3, SIZE);        
    nodePtr3 = (stNode *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd3, 0);
    printf("sender mapped address3 : %p\n", nodePtr3);

    nodePtr1->id = 10001;
    nodePtr1->index = 1;
    strcpy(nodePtr1->name, "KIM CheolMin");
    strcpy(nodePtr1->number,"010-5324.2342");
    strcpy(nodePtr1->group, "Team");
    nodePtr1->pPrev = NULL;
    nodePtr1->pNext = nodePtr2;
    
    nodePtr2->id = 10002;
    nodePtr2->index = 2;
    strcpy(nodePtr2->name,"NAM HyeMin");
    strcpy(nodePtr2->number, "010-3333-2222");
    strcpy(nodePtr2->group, "Security");
    nodePtr2->pPrev = nodePtr1;
    nodePtr2->pNext = nodePtr3;
    
    nodePtr3->id = 10003;
    nodePtr3->index = 3;
    strcpy(nodePtr3->name, "YANG ChangMin");
    strcpy(nodePtr3->number, "010-5879-8156");
    strcpy(nodePtr3->group, "Vehicle");
    nodePtr3->pPrev = nodePtr2;
    nodePtr3->pNext = NULL;
/*
    printf("Node1 : %p %d %s %p %p \n ",nodePtr1, nodePtr1->id, nodePtr1->name, nodePtr1->pPrev, nodePtr1->pNext);
    printf("Node2 : %p %d %s %p %p \n ",nodePtr2, nodePtr2->id, nodePtr2->name, nodePtr2->pPrev, nodePtr2->pNext);
    printf("Node3 : %p %d %s %p %p \n ",nodePtr3, nodePtr3->id, nodePtr3->name, nodePtr3->pPrev, nodePtr3->pNext);
*/

    printf("------- below nodes were added in server -------\n");
	stNode* p = nodePtr1;
    
    int i=0;

    //printf("Node3 : %s\n", nodePtr3->name);
	
    while(p!=NULL){
        printf("%d %p ",i++, p);
		printf("%s\n", p->name);		
		p = p->pNext;
	}
	printf("--------------------------------------\n");


    
    //strcpy(nodePtr[0].name, "KIM CheolMin");
    //strcpy(nodePtr[0].number, "010-5324.2342");
    //strcpy(nodePtr[0].group, "Team");
    

    munmap(nodePtr1, SIZE);
    munmap(nodePtr2, SIZE);
    munmap(nodePtr3, SIZE);

    close(fd1);
    close(fd2);
    close(fd3);

/*
    shm_unlink(NAME1);
    shm_unlink(NAME2);
    shm_unlink(NAME3);
*/  
    return EXIT_SUCCESS;
}
