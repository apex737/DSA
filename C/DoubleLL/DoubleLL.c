#include "DoubleLL.h"

static Node g_HeadNode = {0, "dumHead", "dumPhone", NULL, NULL};
static Node g_TailNode = {0, "dumTail", "dumPhone", NULL, NULL};

void initDLL()
{
    // Head, Tail이 서로를 가리키고 사이의
    // 동적 할당 노드는 없는 상황
    g_HeadNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeadNode;
}

Node* createNode(int id, const char* name, const char* phone)
{
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    if(pNewNode == NULL){
        perror("Node Creation Failed");
        return NULL;
    }
    pNewNode->id = id;
    if(snprintf(pNewNode->name, sizeof(pNewNode->name),
        "%s", name) != LEN)
    {
        fprintf(stderr, "Out of Bound! (Name too long)\n");
        goto err;
    }

    if(snprintf(pNewNode->phone, sizeof(pNewNode->phone),
        "%s", phone) != LEN)
    {
        fprintf(stderr, "Out of Bound! (Phone too long)\n");
        goto err;
    }

    err:
        free(pNewNode);
        return NULL; 
}



int main()
{

    return 0;
}