#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
#include "phonebook.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>				// shm_open
#include <unistd.h>  				// ftruncate
			

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20

void AddNewNodeSample(stList* address_of_list_variables); // 3개의 샘플 노드를 추가한다.

stList list_variables;

void main(){                 // (나중에는 없어질 기능) 3개 샘플 노드를 추가할 것인지 물어보고, 입력에 따라 추가한/안한 후, 메인화면을 띄움.

// 아래는 shared memory 생성 코드
	const int SIZE = 4096; 				// the size of shared memory
	const char *name = "OS";			// the name of shared memory
	const char *message_0 = "Hello, ";
	const char *message_1 = "Shared Memory!\n";
	
	int shm_fd;		// the file descriptor of shared memory
	char *ptr;		// pointer to shared memory
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 			// create the shared memory object 
	ftruncate(shm_fd, SIZE); 									// configure the size of the shared memory
	ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); 			// map the shared memory object
// 위는 shared memory 생성 코드

	char c;
	printf("Do you want add hard-coded sample of nodes? [Y/N]\n");

	while(1){
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y'){
			AddNewNodeSample(&list_variables);
			break;
		}
		else if(c == 'N' || c == 'n'){
			break;
		}
		else{
			printf("Wrong command. Type again.\n");
			continue;
		}

	}
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
