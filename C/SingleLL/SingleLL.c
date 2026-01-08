#include "SingleLL.h"

static Node dummyHead = {0, "dumName", "dumPhone", NULL};
// 더미헤드 vs 포인터
Node* createNode(int id, const char* name, const char* phone)
{
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    if(pNewNode == NULL){
        perror("Node Creation Failed");
        return NULL;
    }
    pNewNode->id = id;
    // 반환형: Integer
    if(snprintf(pNewNode->name, sizeof(pNewNode->name), 
        "%s", name) > LEN)
    {
        // 수정: perror 대신 fprintf 사용
        fprintf(stderr, "Out of Bound! (Name too long)\n");
        goto err;
    }
    if(snprintf(pNewNode->phone, sizeof(pNewNode->phone), 
        "%s", phone) > LEN)
    {
        // 수정: perror 대신 fprintf 사용
        fprintf(stderr, "Out of Bound! (Name too long)\n");
        goto err;
    }
    
    return pNewNode;

    err:
        free(pNewNode);
        return NULL;
}

void insertHead(int id, const char* name, const char* phone)
{
    Node* pNewNode = createNode(id, name, phone);
    if(pNewNode == NULL){
        fprintf(stderr, "InsertHead() Failed");
        return;
    }
    pNewNode->pNext = dummyHead.pNext;
    dummyHead.pNext = pNewNode;    
}

int popHead()
{
    Node* pDelete = dummyHead.pNext;
    if(pDelete == NULL){
        fprintf(stderr, "Empty List\n");
        return -1;
    }
    int ret = pDelete->id;
    dummyHead.pNext = pDelete->pNext;
    printf("[REMOVED] ID: %d, Name: %s, Phone: %s\n", 
            pDelete->id, pDelete->name, pDelete->phone);
    free(pDelete);
    return ret;
}

void insertTail(int id, const char* name, const char* phone)
{
    Node* pNewNode = createNode(id, name, phone);
    Node* pTemp = &dummyHead;
    if(pNewNode == NULL){
        fprintf(stderr, "InsertHead() Failed");
        return;
    }
    
    while(pTemp->pNext) // tailNode까지 이동
    {
        pTemp = pTemp->pNext;
    }
    pTemp->pNext = pNewNode;
}

int popTail(void)
{
    // Tail을 지울 때 이전 노드와 연결해줘야하므로 Prev 도입
    Node* pDelete = dummyHead.pNext;
    Node* pPrevDelete = &dummyHead;

    // find tailNode를 위한 NULL 체크
    if(pDelete == NULL)
    {
        fprintf(stderr, "Empty List\n");
        return -1;
    }

    while(pDelete->pNext)   // find tailNode
    // prev - delete - (next)
    // (next)가 NULL인지 확인하면서 한 칸씩 전진
    {
        pPrevDelete = pDelete;
        pDelete = pDelete->pNext;
    }
    // prev - delete - (NULL)
    int retId = pDelete->id;
    pPrevDelete->pNext = NULL;
    printf("[REMOVED] ID: %d, Name: %s, Phone: %s\n", 
        pDelete->id, pDelete->name, pDelete->phone);
    free(pDelete);
    return retId;
}

void traverse(void)
{
    Node* pTemp = dummyHead.pNext;
    while(pTemp != NULL)
    {
        printf("ID: %d, Name: %s, Phone: %s\n", 
            pTemp->id, pTemp->name, pTemp->phone);
        pTemp = pTemp->pNext;
    }
}

void release(void)
{
    Node* pTemp = dummyHead.pNext;
    Node* pDelete = NULL;
    while(pTemp != NULL)
    {
        pDelete = pTemp;
        pTemp = pTemp->pNext;
        printf("[REMOVED] ID: %d, Name: %s, Phone: %s\n", 
            pDelete->id, pDelete->name, pDelete->phone);
        free(pDelete);
    }
}
