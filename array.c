#include "array.h"


void initArr(myArr* pArr)
{
    memset(pArr->arr, 0, sizeof(pArr->arr));
    pArr->cnt = 0;
}

// Q. 배열에 아무것도 없는 상태라면? 
bool insertItem(myArr* pArr, uint8_t idx, uint8_t val)
{
    if(pArr->cnt >= LEN){
        printf("Arr is Full\n");
        pArr->cnt = LEN;
        return false;
    } 
    
    // 우측에 빈공간이 있는 경우
    {
        // for(uint8_t i = LEN-2; i >= idx; i--)
        for(uint8_t i = LEN-1; i > idx; i--)
        // idx 좌측은 내비두고 >>
        // 덮어쓰는 순서, 경계 확인 (ovf/wrap-around)
        {
            // pArr->arr[i+1] = pArr->arr[i];
            pArr->arr[i] = pArr->arr[i-1];
        }
        pArr->arr[idx] = val;
        pArr->cnt++;
        return true;
    }
}

bool removeItem(myArr* pArr, uint8_t idx)
{
    if(pArr->cnt <= 0){
        printf("Arr is Empty\n");
        pArr->cnt = 0;
        return false;
    } 
    
    {
        for(uint8_t i = idx; i < LEN-1; i++)
        // idx 우측에서부터 <<
        {
            pArr->arr[i] = pArr->arr[i+1];
        }
        pArr->arr[LEN-1] = 0;
        pArr->cnt--;
        return true;
    }
}

void printAll(myArr* pArr)
{
    for(int i = 0; i < LEN; i++)
    {
        printf("%d ", pArr->arr[i]);
    }
    putchar('\n');
}

void putDummy(myArr* pArr)
{
    for(int i = 0; i < LEN; i++)
    {
        insertItem(pArr, i, 2*i+1);
    }
}

