#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

// 상하좌우
// 둘다 0이면 건너뜀

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

vector<int> movable[8] = {
	{},
	{0,1,2,3},
	{0,1},
	{2,3},
	{0,3},
	{1,3},
	{1,2},
	{0,2},
};

struct Node {
	int r, c, d;
};

int board[55][55];
int visited[55][55];
int N, M, L;

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		Node st;
		cin >> N >> M >> st.r >> st.c >> L;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> board[i][j];

		memset(visited, 0, sizeof(visited));

		queue<Node> q;
		q.push(st);
		visited[st.r][st.c] = 1;
		int cnt = 1;
		while (!q.empty())
		{
			Node cur = q.front(); q.pop();
			int p = board[cur.r][cur.c];
			for (int dir = 0; dir < movable[p].size(); dir++)
			{
				int nDir = movable[p][dir];
				int nr = cur.r + dr[nDir];
				int nc = cur.c + dc[nDir];
				if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue;
				if (board[nr][nc] == 0) continue;
				if (visited[nr][nc]) continue;
				visited[nr][nc] = cur.d;
				q.push({ nr,nc,cur.d+1 });
			}
			// 여기서 버그있음
			// 팝 할때마다 카운트가 증가하는게 아니라
			// 거리에 따른 증가니까 차라리 visited에 거리기반 마킹을 해버리고
			// 최댓값을 찍는게 낫다.

			// if (++cnt == L) break;
		}

		int mx = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				mx = max(mx, visited[i][j]);
			}
		cout << "#" << t << " " << mx << "\n";
	}
	return 0;
}