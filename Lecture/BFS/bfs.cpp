/* 백트래킹을 안한다
   코스트가 1로 고정이다
   경로 자체에 관심이 없다 => BFS

*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
struct Edge
{
    int n; // 노드번호
    int d; // 누적거리
};
vector<int> edges[10];
int visited[10];
int bfs(int st, int en)
{
    queue<Edge> q;
    q.push({st, 0});
    visited[st] = 1;
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        if (cur.n == en)
        {
            return cur.d;
        }
        for (int nxt : edges[cur.n])
        {
            visited[nxt] = 1;
            q.push({nxt, cur.d + 1});
        }
    }

    return 0; // 찾지 못함
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    cout << "distance: " << bfs(0, 4) << "\n";

    return 0;
}
