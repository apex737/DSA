#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// 양방향 연결, 그래프 기반
vector<int> edges[5000];
int visited[101];

int N, T;
int main()
{
    cin >> N >> T;
    for (int t = 0; t < T; t++)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    queue<int> q;
    q.push(1);
    visited[1] = 1;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int nxt : edges[cur])
        {
            if (visited[nxt])
                continue;
            visited[nxt] = 1;
            q.push(nxt);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        if (visited[i])
            cnt++;
    cout << cnt - 1 << "\n";
    return 0;
}
