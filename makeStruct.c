#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "double_linked_list.h"


#define NAME "SharedMemory"
#define NUM 3
#define SIZE sizeof(stList)

void AddNewNodeSample (stList* ListPtr);

int main(){
    int fd; 
    if ((fd = shm_open(NAME, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    
    ftruncate(fd, SIZE);
    
    stNode *nodePtr;
    stList *ListPtr;
    stList listPtr;

    ListPtr = (stList *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    printf("sender mapped address : %p\n", nodePtr);

    AddNewNodeSample(&listPtr);

    ListPtr = &listPtr;

    printf("\n\n");
    stNode *p = ListPtr->pHead;
    printf("ID  index  Name  Number  Group\n");
    
    while(p!=NULL){
        printf("%d %d %s %s %s \n", p->id, p->index, p->name, p->number, p->group);
        p = p->pNext;
    }

/*
    nodePtr[0].id = 10001;
    nodePtr[0].index = 1;
    strcpy(nodePtr[0].name, "KIM CheolMin");
    strcpy(nodePtr[0].number, "010-5324.2342");
    strcpy(nodePtr[0].group, "Team");
    nodePtr[0].pPrev = NULL;
    nodePtr[0].pNext = NULL;
*/

    munmap(nodePtr, SIZE);

    close(fd);
    
    return EXIT_SUCCESS;
}

void AddNewNodeSample(stList* address_of_list_variables){                                    // 3개 샘플 노드 강제 추가 함수.

	address_of_list_variables->pHead = (stNode*)malloc(sizeof(stNode));		// list_variables 구조체의 멤버인 pHead(주소)가 가리키게 한다.			// 1번째 노드의 영역을 생성해 주고, 전역변수인 p_head(주소)가 가리키게 한다.
	address_of_list_variables->pHead->id = 10001;
	address_of_list_variables->pHead->index = 1;	
	strcpy(address_of_list_variables->pHead->name, "KIM CheolMin");
	strcpy(address_of_list_variables->pHead->number, "010-5324-2342");
	strcpy(address_of_list_variables->pHead->group, "TEAM");
	//address_of_list_variables->pHead->search_hit = 0;       //예전 멤버
	address_of_list_variables->pHead->matchedValue = 0;
	address_of_list_variables->pHead->favorite = 0;
	address_of_list_variables->pHead->pPrev = NULL;
	address_of_list_variables->pHead->pNext = NULL;
	//list_variables.pHead->pPrev = NULL;  ?? 이렇게 직접적으로 주고 받으면 단점?
	//list_variables.pHead->pNext = NULL;


	stNode* node_sample_2 = (stNode*)malloc(sizeof(stNode));		// 2번째 노드의 영역을 생성해 주고, node_sample_2(주소)가 가리키게 함.
	node_sample_2->id = 10002;
	node_sample_2->index = 2;	
	strcpy(node_sample_2->name, "NAM HyeMin");
	strcpy(node_sample_2->number, "010-3333-2222");
	strcpy(node_sample_2->group, "SECURITY");
	node_sample_2->matchedValue = 0;
	node_sample_2->favorite = 1;
	node_sample_2->pPrev = address_of_list_variables->pHead;							// 2번째 노드이므로, 이 노드의 prev가 첫 번째 노드의 주소인 p_head가 되게 함.
	node_sample_2->pNext = NULL;

	address_of_list_variables->pHead->pNext = node_sample_2;							// 2번째 노드가 추가됐으므로, p_head가 가리키는 첫 번째 노드의 next에 node_sample_2(주소)를 넣음.


	address_of_list_variables->pTail = (stNode*)malloc(sizeof(stNode));		// 3번째 노드의 영역을 생성해 주고, 전역변수인 p_tail(주소)가 가리키게 한다.
	address_of_list_variables->pTail->id = 10003;
	address_of_list_variables->pTail->index = 3;	
	strcpy(address_of_list_variables->pTail->name, "YANG ChangMin");
	strcpy(address_of_list_variables->pTail->number, "010-5879-8156");
	strcpy(address_of_list_variables->pTail->group, "VEHICLE");
	address_of_list_variables->pTail->matchedValue = 0;
	address_of_list_variables->pTail->favorite = 1;
	address_of_list_variables->pTail->pPrev = node_sample_2;							// 3번째 노드이므로, 이 노드의 prev가 2번째 노드의 주소인 node_sample_2가 되게 함.
	address_of_list_variables->pTail->pNext = NULL;

	node_sample_2->pNext = address_of_list_variables->pTail;							// 3번째 노드가 추가됐으므로, node_sample_2가 가리키는 2번째 노드의 next에 p_tail(주소)를 넣음.



	printf("------- below nodes were added -------\n");
	stNode* p = address_of_list_variables->pHead;										// 잘 들어갔는지 테스트 함수.
	while(p!=NULL){
		printf("%s\n", p->name);		
		//printf("%d\n", p->id);
		p = p->pNext;
	}
	printf("--------------------------------------\n");
}

