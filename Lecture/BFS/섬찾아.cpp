#include <iostream>
#include <queue>
using namespace std;

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int board[101][101];
int visited[101][101];
int N, M;
struct Node
{
	int r, c;
};
int main()
{
	cin >> N >> M;
	int cnt = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> board[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			if (board[i][j] && !visited[i][j])
			{
				queue<Node> q;
				q.push({i, j});
				visited[i][j] = 1;
				while (!q.empty())
				{
					auto cur = q.front();
					q.pop();
					for (int dir = 0; dir < 4; dir++)
					{
						int nr = cur.r + dr[dir];
						int nc = cur.c + dc[dir];
						if (visited[nr][nc])
							continue;
						if (!board[nr][nc])
							continue;
						visited[nr][nc] = 1;
						q.push({nr, nc});
					}
				}

				cnt++;
			}
		}

	cout << cnt;
	return 0;
}