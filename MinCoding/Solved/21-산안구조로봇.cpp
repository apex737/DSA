#include <iostream>
#include <vector>
#include <queue>

/*	Dijk

	1. Init: INF, pq(0) 
	2. LD
	3. Relaxation
*/
using namespace std;
int board[31][31];
int D[31][31];

struct Node {
	int r, c, cost;
	bool operator<(const Node& other) const {
		return cost > other.cost;
	}
};

struct Pos {
	int r, c;
};

struct Tunnel {
	Pos st, en;
	int cost;
};

int dc[] = { 1,0,-1,0 };
int dr[] = { 0,1,0,-1 };

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int N; // 보드 너비
		int M; // 터널 개수
		cin >> N >> M;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> board[i][j];
				D[i][j] = 21e8;
			}
		vector<Tunnel> tunnels;
		for (int i = 0; i < M; i++)
		{
			Tunnel t;
			cin >> t.st.r >> t.st.c >> t.en.r >> t.en.c >> t.cost;
			// 주의; 인덱스 보정
			tunnels.push_back({ t.st.r-1, t.st.c-1, t.en.r-1, t.en.c-1, t.cost});
		}

		// Dijk
		priority_queue<Node> pq;
		pq.push({ 0,0,0 });
		D[0][0] = 0;
		while (!pq.empty())
		{
			Node cur = pq.top(); pq.pop();
			// L.D
			if (cur.cost > D[cur.r][cur.c]) continue;

			// 1. 터널 선택 : 현재위치가 터널 st 또는 en
			for (auto t : tunnels)
			{
				int nxtCost;
				if (t.st.r == cur.r && t.st.c == cur.c)
				{
					nxtCost = cur.cost + t.cost;
					if (nxtCost < D[t.en.r][t.en.c])
					{
						D[t.en.r][t.en.c] = nxtCost;
						pq.push({ t.en.r, t.en.c, nxtCost });
					}
				}

				else if (t.en.r == cur.r && t.en.c == cur.c)
				{
					nxtCost = cur.cost + t.cost;
					if (nxtCost < D[t.st.r][t.st.c])
					{
						D[t.st.r][t.st.c] = nxtCost;
						pq.push({ t.st.r, t.st.c, nxtCost });
					}
				}
			}

			// 2. 일반 선택
			for (int i = 0; i < 4; i++)
			{
				int nr = cur.r + dr[i];
				int nc = cur.c + dc[i];
				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
				int nxtCost; 
				int curH = board[cur.r][cur.c];
				int nxtH = board[nr][nc];
				if (curH < nxtH)
					nxtCost = 2 * (nxtH - curH);
				else if (curH == nxtH)
					nxtCost = 1;
				else
					nxtCost = 0;
				nxtCost += cur.cost;
				if (nxtCost < D[nr][nc])
				{
					D[nr][nc] = nxtCost;
					pq.push({ nr,nc,nxtCost });
				}
			}
		}

		cout << "#" << t << " " << D[N-1][N-1] << "\n";
	}
	return 0;
}