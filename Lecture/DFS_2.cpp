#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 어떤 경로로 갔는지 파악하기 위한 배열
int path[2] = {-1, -1};

int curr;
void dfs()
{
    if (curr == 2)
        return;

    for (int i = 0; i < 2; i++)
    {
        curr++;
        path[curr] = i;
        dfs();
        path[curr] = -1;
        curr--;
    }
}
int main()
{
    dfs();
    return 0;
}