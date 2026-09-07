
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
int N;
int stx, sty, enx, eny;
int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};
int board[10][10];
// 다익은 방문표식 필요없다.
// int visited[10][10];

int D[10][10];

int mx, pathCnt;

struct Edge
{
    int y, x, cost;
};
struct cmp
{
    bool operator()(Edge a, Edge b)
    {
        return a.cost < b.cost;
    }
};

int main()
{
    cin >> N;
    cin >> sty >> stx;
    cin >> eny >> enx;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> board[i][j];

    // mx-heap
    priority_queue<Edge, vector<Edge>, cmp> pq;
    pq.push({sty, stx, board[sty][stx]});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (cur.y == eny && cur.x == enx)
        {
            break;
        }

        // lazy
        if (D[cur.y][cur.x] > cur.cost)
            continue;

        for (int i = 0; i < 4; i++)
        {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if (ny >= N || nx >= N || nx < 0 || ny < 0)
                continue;
            if (board[ny][nx] == -1)
                continue;

            int nextCost = D[cur.y][cur.x] + board[ny][nx];
            if (nextCost > D[ny][nx])
            {
                D[ny][nx] = nextCost;
                pq.push({ny, nx, nextCost});
            }
        }
    }
    cout << "pathCnt: " << pathCnt << "\n";
    cout << "mx: " << mx << "\n";
}
