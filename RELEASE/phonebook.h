#ifndef __Phone_Book__
#define __Phone_Book__

extern stNode* ShowList(stList* pList);  // CEB. 정렬된 전체 리스트를 보여주는 함수
extern int SortList(stList* pList);  // CEB. 리스트를 정렬하는 함수 (현재는 이름 오름차순)


extern int ShowNode(stNode* Node, stList* pList); // YM. (YCM이 추가함)
extern stNode* ShowGroup(char* group_name, stList* pList); // JSY. (YCM이 추가함)
extern void AddNewNode(stList* pList); // JIJ. (YCM이 추가함)
extern stNode* searchDisplay(stList* datalist); // YTY. (YCM이 추가함)
extern void Import_Export(stList* list); // NHM. (YCM이 추가함)
extern void ChangeOrder(stList* pList); // YCM이 추가함.
extern void SelectGroup(stList* pList, char* group_name); // YCM이 추가함.

#endif 