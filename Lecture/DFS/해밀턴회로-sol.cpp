#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int N;
int adj[14][14];
int visited;
int mn = INT_MAX;
void dfs(int cur, int sum)
{
    if (sum >= mn)
        return;

    // 처음에 방문표식을 하는 대신에 마지막 돌아오는 간선비용을 더해준다
    if (/* cur == 0 && */ visited == (1 << N) - 1)
    {
        if (adj[cur][0])
        {
            mn = min(mn, sum + adj[cur][0]);
        }
        return;
    }

    for (int nxt = 0; nxt < N; nxt++)
    {
        if (!adj[cur][nxt])
            continue;
        if (!(visited & (1 << nxt)))
        {
            visited |= (1 << nxt);
            dfs(nxt, sum + adj[cur][nxt]);
            visited &= ~(1 << nxt);
        }
    }
}
int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> adj[i][j];

    visited |= (1 << 0);
    dfs(0, 0);
    visited &= ~(1 << 0);
    cout << mn << "\n";
    return 0;
}