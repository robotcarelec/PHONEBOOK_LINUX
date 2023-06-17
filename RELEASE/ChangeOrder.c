#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "double_linked_list.h"
//#include "phonebook.h"

// For Share Memory
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define NAME2 "SharedMemory2"
#define SIZE2 sizeof(stList)

int main(){                                                         // 테스트용.

    int fd2; 
    if ((fd2 = shm_open(NAME2, O_CREAT | O_RDWR, 0600)) <0 ){
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    
    stList *listPtr;
    listPtr = (stList *)mmap(0, SIZE2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
	
    int command;
	printf("-------- sort by --------\n1. number\n2. group\n3(or else). name\n-------------------------\n\n");
	printf("Input your command number: ");
		scanf("%d", &command);
	//printf("your choice: %d\n", command);
	
	switch (command) {
                case 1: printf("your choice is: by number\n");
						break;
                case 2: printf("your choice is: by group\n");
						break;
                default: printf("your choice is: by name\n");
						break;
            }
	listPtr->sort_order = command;
}
