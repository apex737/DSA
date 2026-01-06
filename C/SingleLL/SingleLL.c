#include "SingleLL.h"

typedef struct {
    int id;
    const char* name;
    const char* phone;
    struct Node* pNext;
} Node;

// 더미헤드 vs 포인터
Node* createNode(int id, const char* name, const char* phone)
{
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->id = id;
    strcpy_s()
}

int main()
{

    return 1;
}