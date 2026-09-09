#include <iostream>
#include <queue>
using namespace std;

struct Pos
{
    int r, c, d;
};

int visited[10][10];
int board[10][10];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int main()
{
    int r, c;
    cin >> r >> c;
    queue<Pos> q;
    visited[r][c] = 1;
    board[r][c] = 1;
    q.push({r, c, 1});
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if (nr < 0 || nc < 0 || nr >= 5 || nc >= 5)
                continue;
            if (visited[nr][nc])
                continue;

            visited[nr][nc] = 1;
            board[nr][nc] = cur.d + 1;
            q.push({nr, nc, cur.d + 1});
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
    return 0;
}