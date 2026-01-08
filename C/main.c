#include "SingleLL/SingleLL.h"

void testSLL(void)

{
    insertHead(1, "Hoon", "010-1234-1234");
    insertHead(2, "Joon", "010-1234-1234");
    insertHead(3, "Koon", "010-1234-1234");
    insertTail(4, "Poon", "010-1234-4321");
    insertTail(5, "Yoon", "010-4321-4321");
    popTail();
    popHead();
    traverse();
    release();
    puts("Test Done");
}

int main()
{
    testSLL();

    return 0;
}