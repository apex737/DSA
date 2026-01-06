#include "SingleLL.h"

typedef struct {
    int id;
    char name[LEN];
    char phone[LEN];
    // const char* name;
    // const char* phone;
    struct Node* pNext;
} Node;



// 더미헤드 vs 포인터
Node* createNode(int id, const char* name, const char* phone)
{
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->id = id;
    // strcpy_s 대용
    int retName = snprintf(pNewNode->name, sizeof(pNewNode->name), "%s", name);
    int retPhone = snprintf(pNewNode->phone, sizeof(pNewNode->phone), "%s", phone);
    pNewNode->pNext = NULL;
    if(retName >= sizeof(pNewNode->name) || 
        retPhone >= sizeof(pNewNode->phone))
        {
            releaseNode(pNewNode);
            printf("Node Creation Failed\n");
            return NULL;
        }
    return pNewNode;
}

void releaseNode(Node* pNode)
{
    free(pNode);
}


int main()
{
    Node* pMyNode;
    pMyNode = createNode(1, "hoonhoonhoonhoonhoonhoon", "010-1234-1234");
    releaseNode(pMyNode);
    return 0;
}