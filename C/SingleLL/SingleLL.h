#ifndef SINGLE_LL_H
#define SINGLE_LL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LEN         20

typedef struct Node { // Tag 
    int id;
    char name[LEN];
    char phone[LEN];
    struct Node* pNext;
} Node;              // Alias 

Node* createNode(int id, const char* name, const char* phone);
void insertHead(int id, const char* name, const char* phone);
int popHead(void);
void insertTail(int id, const char* name, const char* phone);
int popTail(void);
void traverse(void);
void release(void);

#endif