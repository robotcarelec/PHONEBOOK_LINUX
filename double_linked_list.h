#ifndef __Double_Linked_List__
#define __Double_Linked_List__

#define NAME_LENGTH 30
#define NUMBER_LENGTH 20
#define GROUP_LENGTH 20

typedef struct __Node {    
    int id;             // 노드 고유의 번호 10001부터 시작
    int index;         // 정렬한 후 일렬번호
    char name[NAME_LENGTH];     // 영문 이름
    char number[NUMBER_LENGTH]; // 전화 번호
    char group[GROUP_LENGTH];
    bool matchedValue; // search_hit → matchedValue (230108). 해당 노드가 검색조건을 만족한다면 이 flag를 1로 설정해서 다음함수로 넘겨줌 메인메뉴로 돌아갈 때 0으로 초기화 필요
    bool favorite; // 즐겨찾기
    
    //struct __Node* pPrev;
    int pPrev;
    //struct __Node* pNext;    
    int pNext;    
} stNode;  // 노드 구조체 

typedef struct __List {
    //stNode* pHead;
    int pHead;
    //stNode* pTail;    
    int pTail;    
    bool sort_needs;
    int sort_order;
    int count_node;
} stList;   // 리스트 구조체

// YTY 구조체. github - TY 브랜치에서 이 부분만 복붙함.
typedef struct __SearchedList
{
    struct __SearchedList* NextNode;
    struct __SearchedList* PrevNode;
    stNode* node;
    int matchedWith;
} stSearchedList;  // 검색된 리스트를 가지는 구조체

// 함수 선언
extern void InitializeList(stList* pList);              // 메모리 할당해서 리스트 만들기
stNode* MakeNode(stNode* data);                //메모리 할당해서 노드 만들기
extern void AddtoTailNode(stList* pList, stNode* data);  //Tail에 노드 추가
extern void AddtoHeadNode(stList* pList, stNode* data);   // Head에 노드 추가
extern void DeleteNode(stList* pList, int index);        // 현재 노드 삭제 하기 (id 기준)
extern void PrintList(stList* pList);                 // 전체 리스트 출력하기
extern int IsEmpty(stList *pList) ;
extern void CountNode(stList *pList);

#endif 