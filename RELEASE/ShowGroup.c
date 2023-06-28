#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include "double_linked_list.h"

// For Share Memory
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define NAME "SharedMemory"
#define NUM 100
#define SIZE sizeof(stNode)

#define NAME2 "SharedMemory2"
#define SIZE2 sizeof(stList)

//extern stNode* ShowGroup(char* group_name, stList* pList)
int main(){
//printf("here ok\n");
    // 공유 메모리 받아오기. 
    int fd; 
    if ((fd = shm_open(NAME, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
        
    stNode *nodePtr;
    nodePtr = (stNode *)mmap(0, NUM*SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int fd2; 
    if ((fd2 = shm_open(NAME2, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
        
    stList *pList;
    pList = (stList *)mmap(0, SIZE2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	//stList 공유 메모리 끝.

	//그룹별 보여주기를 위한 list 생성 (initializelist 변형)
	ostList* group_list = (ostList*) malloc(sizeof(ostList));
	//group_list->pHead = pList->pTail = NULL; // 첫,끝 노드 null로 설정
	group_list->pHead = group_list->pTail = NULL; // 첫,끝 노드 null로 설정
//	group_list->pHead = pList->pTail = -1; // 첫,끝 노드 -1로 설정
	group_list->sort_needs = 1;
	group_list->sort_order = 2;
	group_list->count_node = 0; // 현재 노드 수 : 0
	int selectedIndex;
	//ostNode* selectedNode;
	stNode* selectedNode;
	//ostNode* curr_node = NULL;
	stNode* curr_node;
	
	// 원래 노드의 주소값으로 판별하던 것을 → 노드 배열의 인덱스값으로 판별해야 하므로, 인덱스를 저장할 변수 n 선언.
	int n = pList->pHead;

//printf("here2 ok\n");

	//for (curr_node = pList->pHead; curr_node != NULL; curr_node = curr_node->pNext)	
	for (curr_node = nodePtr + n; n != -1; n = curr_node->pNext, curr_node = nodePtr + n)
	{
//printf("here3 ok\n");
//printf("n: %d\n", n);
//printf("pList->group_name: %s\n", pList->group_name);
//printf("curr_node->group: %s\n", curr_node->group);
		//if (strcmp(group_name, curr_node->group) == 0) //지나가면서 group명이 같다면
		if (strcmp(pList->group_name, curr_node->group) == 0) //(230617) group_name을 pList로부터 읽어오도록 변경.
		{
//printf("here4 ok\n");
			//group_list에 추가해주기 
			ostNode* temp = malloc(sizeof(ostNode));
			temp->id = curr_node->id;
			temp->index = curr_node->index;
			strcpy(temp->name, curr_node->name);
			strcpy(temp->number, curr_node->number);
			strcpy(temp->group, curr_node->group);
			temp->favorite = curr_node->favorite;
			AddtoTailNode(group_list, temp); //List의 뒤에 신규 노드 추가 
//printf("here5 ok\n");
		}
	}
	//추가한 list를 정렬해주기(이름순으로)
	//SortList(group_list);
    PrintList(group_list); 
	
//printf("here6 ok\n");

	ostNode* o_curr_node = group_list->pHead;
	ostNode* o_selectedNode;
	//n = group_list->pHead;

	printf("\nSelect index...."); // 검색 결과 리스트 중 1개의 index값을 입력 받음
	printf("\n(If you want to come back Main Menu, Input '0')....");
	scanf("%d",&selectedIndex);

	while(o_curr_node != NULL)
	{
		if(selectedIndex == 0){
			//o_selectedNode = NULL;
			//break;
			return 0;
		}
		else{
			if(selectedIndex == o_curr_node->index){
				o_selectedNode = o_curr_node;
				break;
			}    
		}
		o_curr_node = o_curr_node->pNext;
		//n = curr_node->pNext;

	}
	
//	return selectedNode; 
	//return selectedNode - nodePtr; //(230617) 노드 배열의 인덱스값을 리턴하도록 변경.


	n = pList->pHead;
	stNode* currentNode; // 현재 stNode의 주소값 저장위한 변수
	while(n != -1){
        currentNode = &nodePtr[n];
		if (currentNode->id == o_selectedNode->id){
			//return currentNode - nodePtr; //(230617) 노드 배열의 인덱스값을 리턴.
			pList->return_value = currentNode - nodePtr; //(230628) 노드 배열의 인덱스값을 리턴값에 저장.
			return 1;
		}
        n = currentNode->pNext;
    }
	return 0;
}

