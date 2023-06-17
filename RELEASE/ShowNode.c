#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "double_linked_list.h"
#include "phonebook.h"

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


static void subMenu(stNode* Node, stList* pList);
static void EditMenu(stNode* Node, stList* pList);
static void EditName(stNode* Node);
static void EditNumber(stNode* Node);
static void EditGroup(stNode* Node);
static void EditFavorate(stNode* Node);
static void StartCalling(stNode* Node);
static int PrintShowNode(stNode* Node);

// For Share Memory
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define NAME "SharedMemory"
#define NAME2 "SharedMemory2"
#define NUM 100
#define SIZE sizeof(stNode)
#define SIZE2 sizeof(stList)

//extern int ShowNode(stNode* Node, stList* pList) {
//int main(stNode* Node, stList* pList){    
int main(int argc, char* argv[]){    

    // 매개변수 잘 받았는지 확인
        printf("argc = %d\n", argc);

    int i;
    for(i = 0; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    // 확인 끝

    // char형으로 받은 argv[1]을 int형으로 변환. 배열의 index로 사용하기 위함.
    int n = *argv[1] - 48;

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
        
    stList *pList;
    pList = (stList *)mmap(0, SIZE2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	//stList 공유 메모리 끝.
    


    // 없어도 되는 코드인 듯
    stNode* tmp_stNode;
    tmp_stNode = &nodePtr[n];    

   //system("clear");


    //printf("%5d ", Node->id);
    printf("%5d ", tmp_stNode->id);
    printf("%3d ", tmp_stNode->index);
    printf("%30s ", tmp_stNode->name);
    printf("%20s ", tmp_stNode->number);
    printf("%20s ", tmp_stNode->group);
    printf("%3d", tmp_stNode->favorite);
    printf("\n");
    //printf("%3d ", Node->index);
    //printf("%30s ", Node->name);
    //printf("%20s ", Node->number);
    //printf("%20s ", Node->group);
    //printf("%3d", Node->favorite);
    //printf("\n");

    subMenu(tmp_stNode, pList);    
  
    return 0;
}


static void subMenu(stNode* Node, stList* pList) {
    
    int i=0;   
    int index = Node->index;

    while (i< 4) {
        
        printf("\n");
        printf("****Sub Menu****\n");
        printf("1: Delete \n");
        printf("2: Edit \n");
        printf("3. Calling \n");
        printf("4. Go to Main Menu \n");
        printf("Press number: ");
        scanf("%d", &i);

        
        if (i == 1) {
           //DeleteNode(pList, index);
           printf("Delete Success \n");
           system("clear");
           
        }

       else if (i == 2) {
           EditMenu(Node,pList);
           //SortList(pList);
       }

       else if (i == 3) {
            StartCalling(Node);
       }      

      else {
            break;
           
        }
       
    }
    return;
    
}


static void EditMenu(stNode* Node, stList* pList) {
    int num = 0;
    int j = 0;
   

    system("clear");


    while (j < 5) {

        printf("%5d ", Node->id);
        printf("%3d ", Node->index);
        printf("%30s ", Node->name);
        printf("%20s ", Node->number);
        printf("%20s ", Node->group);
        printf("%3d", Node->favorite);
        printf("\n");

        while (num < 5) {
            printf("\n");
            printf("1: Name \n");
            printf("2: Phone Number \n");
            printf("3. Group \n");
            printf("4. Favorate \n");
            printf("5. sub Menu \n");
            printf("Press number: ");
            scanf("%d", &num);

            switch (num)
            {
            case 1:
                EditName(Node);

                break;
            case 2:
                EditNumber(Node);

                break;
            case 3:
                EditGroup(Node);

                break;
            case 4:
                EditFavorate(Node);

                break;
            default:
                break;
            }
            break;
        }
        j = num;

    }
    system("clear");
    PrintShowNode(Node);
    subMenu(Node, pList);
    return;

}


static void EditName(stNode *Node) {

    printf("New name: ");
    scanf("%s", Node->name);                        

    system("clear");
}


static void EditNumber(stNode* Node) {

    printf("New number: ");
    scanf("%s", Node->number);    

    system("clear");
}


static void EditGroup(stNode* Node) {
    
    printf("New Group: ");
    scanf("%s", Node->group);

    system("clear");
}

static void EditFavorate(stNode* Node) {
   
    int scalar = 0;
    bool b = false;   
 
    printf("New Favorate: ");
    scanf("%d", &scalar);
    b=(bool)scalar;
    Node->favorite = b;

    system("clear");

}

static void StartCalling(stNode* Node) {
    int num;
    int i;    

    while (1) 
    {
        system("clear");
        PrintShowNode(Node);
       
        for (i = 0;i < 5; i++) {
            printf(ANSI_COLOR_RED "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_GREEN "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_YELLOW "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_BLUE "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_MAGENTA "*Calling*" ANSI_COLOR_RESET "");
            printf(ANSI_COLOR_CYAN "*Calling*" ANSI_COLOR_RESET "\n");

            sleep(1);

        };

        printf("If you want to hang up, press 1:   ");
        scanf("%d", &num);

        if (num == 1) { 
            system("clear");
            PrintShowNode(Node);
            break;
        }

     }
 }
 

static int PrintShowNode(stNode* Node) {

   
    system("clear");

    printf("%5d ", Node->id);
    printf("%3d ", Node->index);
    printf("%30s ", Node->name);
    printf("%20s ", Node->number);
    printf("%20s ", Node->group);
    printf("%3d", Node->favorite);
    printf("\n");   
    

    return 0;
}


