#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "double_linked_list.h"




// 함수 구현
extern void InitializeList(ostList* pList) {
    ostList* list = malloc(sizeof(ostList));
    list->pHead = list->pTail = NULL;
    list->sort_needs = 1;
    list->sort_order = 0;
    list->count_node = 0;
}

extern ostNode* MakeNode(ostNode* data) {
    ostNode* node = malloc(sizeof(ostNode));
    node = data;
    node->pPrev = node->pNext = NULL;
    // id 부여하는 방법을 추가 고민
    return node;
}  //노드를 만들기 위해 메모리 할당하고 초기화하기

extern void AddtoTailNode(ostList* pList, ostNode* data) {   // 노드를 tail에 노드 추가
    ostNode* node = MakeNode(data);
    if(IsEmpty(pList)) {
        pList->pHead = pList->pTail = node;   
    } else {
        node->pPrev = pList->pTail;
        node->pNext = NULL;
        pList->pTail->pNext = node;        
        pList->pTail        = node;
    }
}  //List의 뒤에 신규 노드 추가



extern void AddtoHeadNode(ostList* pList, ostNode* data) { //노드를 Head에 추가    
    ostNode* node = MakeNode(data);
    if(IsEmpty(pList)) {
        pList->pHead = pList->pTail = node;   
    } else {       
        node->pNext = pList->pHead;
        pList->pHead->pPrev = node; 
        pList->pHead = node;
        node->pPrev = NULL;    
    }
}  

// (230702) DeleteNode()를 ShowNode.c로 이동.

extern void PrintList(ostList* pList) {
    ostNode* cur;
    for (cur = pList->pHead; cur !=NULL ; cur=cur->pNext) {
        printf("%5d ", cur->id);
        printf("%3d ",cur->index);
        printf("%30s ",cur->name);
        printf("%20s ",cur->number);
        printf("%20s ",cur->group);
        printf("%3d", cur->favorite);
        printf("\n");
    }
    printf("\n");
}

extern int IsEmpty(ostList* pList) {
    return (pList->pHead == NULL);
} // 리스트가 비어있는 지 확인

extern void CountNode(ostList *pList) {
    int count=0;
    ostNode* cur;
    for (cur = pList->pHead; cur !=NULL ; cur=cur->pNext) {
        count++;
    } 
    (*pList).count_node = count;  
//    printf("%d\n",count);
}