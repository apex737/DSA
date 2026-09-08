#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int N;
int adj[14][14];
int visited[14];
int mn = INT_MAX;
bool first_flag = true;

void dfs(int cur, int dist, int cnt)
{
    if (cur == 1 && !first_flag)
    {
        if (cnt == N && dist < mn)
        {
            mn = dist;
        }
        return;
    }
    else
    {
        return;
    }

    for (int nxt = 1; nxt <= N; nxt++)
    {
        if (visited[nxt])
            continue;
        if (!adj[cur][nxt])
            continue;
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> adj[i][j];

    dfs(1, 0, 0);
    return 0;
}