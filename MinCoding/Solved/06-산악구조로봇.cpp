#include <iostream>
#include <queue>

using namespace std;

int D[31][31];
int board[31][31];
int N;

struct Node {
	int r, c, cost;
	// 우선순위가 other에 밀릴 조건은 cost가 더 큰 경우이다.
	bool operator<(const Node& other) const {
		return cost > other.cost;
	}
};

int dc[] = { 1, 0,-1,0 };
int dr[] = { 0,1,0,-1 };

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
				D[i][j] = 21e8;
			}

		priority_queue<Node> pq;
		/*	Dijk 정규형 (Init - Lazy Deletion - Relaxation)

			1. INF 초기화
			2. lazy-deletion; 꺼낸 뒤, D와 비교해서 비싸면 드랍 
			3. relaxation; 더 싼 경로를 찾으면 cost 갱신
		*/
		pq.push({ 0,0,0 });
		D[0][0] = 0;
		while (!pq.empty())
		{
			auto cur = pq.top(); pq.pop();
			// lazy del
			if (cur.cost > D[cur.r][cur.c]) continue;
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
				if(nxtCost < D[nr][nc]) 
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