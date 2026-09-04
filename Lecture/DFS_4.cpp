#include <iostream>
int cnt;
bool flag;
int path[3] = {-1};
using namespace std;

void dfs(int cur)
{
    cnt++;
    if (cnt == 6)
    {
        flag = 1;
        for (int i = 0; i < 3; i++)
            cout << path[i] << " ";
        cout << "\n";
        return;
    }

    if (cur == 3)
        return;

    for (int i = 0; i < 2; i++)
    {
        path[cur] = i;
        dfs(cur + 1);
        if (flag)
            return;
    }
}

int main()
{
    dfs(0);
    return 0;
}