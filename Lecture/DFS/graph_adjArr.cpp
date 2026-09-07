#include <iostream>
#include <algorithm>

using namespace std;
int node_cnt;
int adj[10][10];
int st, en;
int visited[10];
int max_cost;
int total_cnt;

void dfs(int cur, int sum)
{
    if (cur == en)
    {
        max_cost = max(max_cost, sum);
        /* ------ */
        total_cnt++;
        return;
    }
    // adj[st][en]으로 다음값 갱신
    for (int nxt = 0; nxt < node_cnt /* ----- */; nxt++)
    {
        if (visited[nxt])
            continue;
        // 0은 여기서 끊겨있다는 의미니까
        if (!adj[cur][nxt])
            continue;
        visited[nxt] = 1;
        dfs(nxt, sum + adj[cur][nxt]);
        visited[nxt] = 0;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> node_cnt;
    for (int i = 0; i < node_cnt; ++i)
        for (int j = 0; j < node_cnt; ++j)
            cin >> adj[i][j];

    cin >> st >> en;
    //
    visited[st] = 1;
    dfs(st, 0);

    cout << max_cost << "\n"
         << total_cnt << "\n";
}
