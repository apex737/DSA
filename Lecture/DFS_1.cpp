#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 어떤 경로로 갔는지 파악하기 위한 배열
int path[2] = {-1, -1};

void dfs(int curr)
{
    if (curr == 2)
        return;

    for (int i = 0; i < 2; i++)
    {
        // 기록은 들어가기 전에
        // cout << "Depth: " << curr << " " << "index: " << i << "\n";
        path[curr] = i;
        dfs(curr + 1);
        // 원복은 나가고 난 뒤
        path[curr] = -1;
    }
}
int main()
{
    dfs(0);
    return 0;
}