#ifndef ARRAY_H
#define ARRAY_H
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"

#define LEN     7

typedef struct 
{
    uint8_t arr[LEN];
    uint8_t cnt;
} myArr;

void initArr(myArr* pArr);
bool insertItem(myArr* pArr, uint8_t idx, uint8_t val);
bool removeItem(myArr* pArr, uint8_t idx);
void printAll(myArr* pArr);
void putDummy(myArr* pArr);

#endif