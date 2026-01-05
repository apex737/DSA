<<<<<<< HEAD
#include "array.h"

void test1(void)
{
    /* Static Array
    1. Insert
    2. Delete */ 
    myArr mArr;
    initArr(&mArr);
    putDummy(&mArr);
    removeItem(&mArr, 3);
    insertItem(&mArr, 1, 100);
    removeItem(&mArr, 2);
    insertItem(&mArr, 0, 99);
    printAll(&mArr);
}

int main()
{
    
/* Dynamic Array
   1. Create/Read 
   2. Write
   3. Insert
   4. Delete */ 

   
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset 사용을 위해 추가
#include "myQ.h"

void test_osrq()
{
    for(int i = 0; i < 10; i++)
    {
        SORQ_enqueue(i);
    }

    for(int i = 0; i < 10; i++)
    {
        
        printf("SORQ_dequeue( %d )\n", SORQ_dequeue());
    }

    SORQ_enqueue(14);
    SORQ_enqueue(41);
    printf("SORQ_dequeue( %d )\n", SORQ_dequeue());
}

void test_cntq()
{
    for(int i = 0; i < 15; i++)
    {
        CNTQ_enqueue(i);
    }

    for(int i = 0; i < 10; i++)
    {
        
        printf("CNTQ_dequeue( %d )\n", CNTQ_dequeue());
    }

    CNTQ_enqueue(14);
    CNTQ_enqueue(41);
    printf("CNTQ_dequeue( %d )\n", CNTQ_dequeue());
}

void test_mskq()
{
    for(int i = 0; i < 15; i++)
    {
        MSKQ_enqueue(i);
    }

    for(int i = 0; i < 5; i++)
    {
        MSKQ_enqueue(i);
    }

    for(int i = 0; i < 10; i++)
    {
        
        printf("MSKQ_dequeue( %d )\n", MSKQ_dequeue());
    }

    MSKQ_enqueue(14);
    MSKQ_enqueue(41);
    printf("MSKQ_dequeue( %d )\n", MSKQ_dequeue());
}




int main()
{
    
    
    
>>>>>>> 228f2b7a863cf889e327793e48e1eca6ef38f614
    return 1;
}