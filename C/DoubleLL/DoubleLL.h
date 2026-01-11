#ifndef DOUBLE_LL_H
#define DOUBLE_LL_H

#include "../def.h"
typedef struct Node
{
    int id;
    char name[LEN];
    char phone[LEN];
    struct Node* pNext;
    struct Node* pPrev;
} Node;

#endif

