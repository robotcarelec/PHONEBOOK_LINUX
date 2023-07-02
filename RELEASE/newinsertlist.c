// (230627) double_linked_list.h 내부 함수와 충돌나는 이름은 모두 뒤에 "2"를 붙여줬습니다.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "double_linked_list.h"
//#include "phonebook.h"

// For Share Memory
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define NAME "SharedMemory"
#define NAME2 "SharedMemory2"
#define NUM 100
#define SIZE sizeof(stNode)
#define SIZE2 sizeof(stList)

//함수선언 : ID 빈자리 찾기, 새로운 노드에 인댁스 추가 하기
void AddNewNode(stList* pList, stNode* data);
int searchVacantIDadd(stList* pList, stNode* data);
int addedIndex(stList* pList, stNode* data);
void AddtoTailNode2(stList* pList, stNode* data);
int maxValue(stList* pList, stNode* pNode);

int IsEmpty2(stList* pList) {
    return (pList->pHead == -1);
} // 리스트가 비어있는 지 확인

int main(int argc, char* argv[]){    


    // 공유 메모리 받아오기
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
    
    stList *listPtr;
    listPtr = (stList *)mmap(0, SIZE2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	
	printf("read from shared memory... \n\n");
	for (int k=0 ; k<9 ; k++){
            printf("[Index %d] %d %d %s %s %s %d %d \n",k, nodePtr[k].id,nodePtr[k].index, nodePtr[k].name, nodePtr[k].number, nodePtr[k].group,nodePtr[k].pPrev,nodePtr[k].pNext);
        }
	
	printf("\n\nHead index : %d\n", listPtr->pHead);
	printf("Tail index : %d\n", listPtr->pTail);
	//stList 공유 메모리 끝.

	AddNewNode(listPtr, nodePtr);
	
	
	printf("After added... \n\n");
	for (int k=0 ; k<15 ; k++){
            printf("[Index %d] %d %d %s %s %s %d %d \n",k, nodePtr[k].id,nodePtr[k].index, nodePtr[k].name, nodePtr[k].number, nodePtr[k].group,nodePtr[k].pPrev,nodePtr[k].pNext);
        }

	return 0;
}





 void AddNewNode(stList* pList, stNode* pNode) {
	char sName[NAME_LENGTH];
	char sPhoneNumber[NUMBER_LENGTH];
	char sGroup[GROUP_LENGTH]; //헤더에서 정의된 값을 사용
	//stNode* newData; //= malloc(sizeof(stNode)); //변수 형으로 생성생성되는 데이터는 1개 이므로 노드변수 하나만 생성
	char favorite;
	 
	int newIndex =0;
	
	if(pList->pHead == -1){
		printf("** Phonbook list is vacant");
		return;
		
	}else{
		printf("** Welcome Phonebook input form           **\n");
		printf("** please press the enter key after input **\n");
		printf("** type 'q' if you want exit\n\n");
		printf("Name : ");
		scanf(" %[^\n]s", sName);
		
		printf("Phone numbers : ");
		scanf(" %[^\n]s", sPhoneNumber);
		printf("Group : ");
		scanf(" %[^\n]s", sGroup);
	
		printf("Is favorite? : (y/n) :");
		favorite = getchar();
	}

	newIndex = addedIndex(pList, pNode); //지워져서 비어진 배열 방위치
	
	while(1) { //즐겨찾기 입력 y 또는 n 입력을 받고 그 외의 문자는 루프에서 돈다. 
		//scanf("%c",&favorite);
		
		if(favorite == 'y') {
			pNode[newIndex].favorite = 1;
			break;
		}else if (favorite == 'n') {
			pNode[newIndex].favorite = 0;
			break;
		}else {
			printf("Please input 'y' or 'n'\n");
			printf("Is favorite? : (y/n) :");
			favorite = getchar();
			continue;
		}
	}
	
	

	
	strcpy(pNode[newIndex].name, sName);
	strcpy(pNode[newIndex].number, sPhoneNumber);
	strcpy(pNode[newIndex].group, sGroup); // 새로운 데이터 노드에 입력된 값을 추가
	
	pNode[newIndex].index = maxValue(pList, pNode) + 1; //가장 큰 맥스 인덱스에다가 +1
	pNode[newIndex].id = searchVacantIDadd(pList, pNode); //id 빈자리 찾아서 전 노드 id+1 추가하기
	 
	
	pNode[pList->pTail].pNext = newIndex;
	pNode[newIndex].pPrev = pList->pTail;
	pList->pTail = newIndex;
	pNode[newIndex].pNext = -1; 
	
	//AddtoTailNode(pList, newData);  // 새로운 데이터가 들어간 구조체 노드를 tail에 노드 추가, double_linked_list에 정의됨.
	pList->sort_order = 1; //다시 소팅하는 플래그 넣기
	
}

int searchVacantIDadd(stList* pList, stNode* pNode) {
	int newID = 0;
	//int cnt = 0 ;
	int i = 0;
	int chkID[10000] = {0,}; //0으로 초기화
	int curindex = pList->pHead;
	
	while(curindex != -1){ // 공유 메모리 링크 돌리기
		chkID[pNode[curindex].id % 10000] = pNode[curindex].id;
		
		curindex = pNode[curindex].pNext;
	}
	
	for(i = 1; i < 10000 ; i++) { //배열의 시작을 1부터 했기 때문에 1부터 시작한다. 
		
	
		if(chkID[i] == 0) { // 1부터 카운트 해서 비어있는 칸의 첫번째 칸을 찾는다. 모두 차있다면 
			newID = i + 10000; //ID의 구조는 1xxxx이므로 저장된 배열에 인덱스 값을 넣으면 ID완성
			return newID;
		}
	}
	
}



int addedIndex(stList* pList, stNode* pNode) {
	int newIndex = 0;
	int curindex = pList->pHead; // index 넘기기용
		printf("HEAD is : %d\n",curindex);
	
	int i = 0;
	int chkIndex[10000] = {0,}; //0으로 초기화
	
	while(curindex != -1){ // 공유 메모리 링크 돌리기
		chkIndex[curindex] = curindex;
		
		curindex = pNode[curindex].pNext;
	}
	
	for(i = 1; i < 10000 ; i++) { //배열의 시작을 1부터 했기 때문에 1부터 시작한다. 
		
	
		if(chkIndex[i] == 0) { // 1부터 카운트 해서 비어있는 칸의 첫번째 칸을 찾는다. 
			newIndex = i; //
			return newIndex;
		}
	}
	
}

int maxValue(stList* pList, stNode* pNode){
	int curindex = pList->pHead; // index 넘기기용
		printf("HEAD is : %d\n",curindex);
	
	int i = 0;
	int maxNum = 0;
	
	while(curindex != -1){ // 공유 메모리 링크 돌리기
		if(maxNum < pNode[curindex].index){
			maxNum = pNode[curindex].index;
		}
		
		curindex = pNode[curindex].pNext;
	}
	
	return maxNum;
}


void AddtoTailNode2(stList* pList, stNode* data) {   // 노드를 tail에 노드 추가
    //stNode* node = MakeNode(data);
    
	
	if(IsEmpty2(pList)) {
        pList->pHead = pList->pTail = -1;   
    } else {
        data->pPrev = pList->pTail;
        pList->pTail = data->index-1;
		data->pNext = -1;
    }
}  //List의 뒤에 신규 노드 추가

int countList(stList* pList, stNode* pNode){
	int cnt = 0;
	int nodes = 0;
	for(nodes = pList->pHead ; pNode->index-1 != pList->pTail ; nodes = pNode->pNext){
		cnt++;
	}
	return cnt;
	
}
