#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

char path[4];

void func(int lev)
{
    if (lev == 3)
    {
        cout << path << '\n';
        return;
    }
    for (int = 0; i < 3; i++)
    {
        path[lev] = 'A' + i;
        func(lev + 1);
        path[lev] = '\0';
    }
}

int main()
{
    // freopen("sample_input.txt", "r", stdin);
    func(0);
    return 0;
}
