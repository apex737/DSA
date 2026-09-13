#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int N, M;
#define R first
#define C second

struct Edge
{
  int r, c;
  int cost;
};

struct Tunnel
{
  pair<int, int> st, en;
  int cost;
};

vector<Tunnel> tunnels;
int board[33][33];
int D[33][33];

struct cmp
{
  bool operator()(Edge a, Edge b) { return a.cost > b.cost; }
};

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N >> M;
    tunnels.assign(M, {});
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
      {
        cin >> board[i][j];
        D[i][j] = 1e9;
      }
    for (int i = 0; i < M; i++)
    {
      cin >> tunnels[i].st.R >> tunnels[i].st.C;
      cin >> tunnels[i].en.R >> tunnels[i].en.C;
      cin >> tunnels[i].cost;
    }

    priority_queue<Edge, vector<Edge>, cmp> pq;
    // 다익스트라
    pq.push({1, 1, 0});
    D[1][1] = 0;

    while (!pq.empty())
    {
      Edge cur = pq.top();
      pq.pop();

      // ***************** 핵심. Lazy Deletion ***************** //
      // 다익스트라에서 Optimum을 보장하기 위한 핵심 필터링

      /* PQ에서 꺼낸 값이 현재 D-table과 일치하면, 그 순간 Optimum 확정.
      *  PQ에서 꺼낸 가장 최신값이 Optimum이고, Lazy Deletion이란
      *  나머지 후보들을 제거하는 과정이다. */
      if (cur.cost > D[cur.r][cur.c])
        continue;

      // 여기서부터 cur은 무조건 Optimum이다.
      if (cur.r == N && cur.c == N)
        break;

      // 만약 현재 위치가 터널 입출구라면 터널 출입구에 대해서 완화
      /* 다익스트라 Relaxation
      => 다음 위치의 Cost가 D 보다 싸면
        1. D를 갱신하고
        2. pq에 그 위치를 삽입
        => 넣은 시점에서는 (i, j) 최단거리 "후보"이고, 뽑히면 Optimum 확정
        => 추후 lazy deletion을 통해 최초로 뽑히지 못한 후보들을 제거
      */
      int nextCost;
      for (const Tunnel &tunnel : tunnels)
      {
        // st -> en
        int nr, nc;
        if (cur.r == tunnel.st.R && cur.c == tunnel.st.C)
        {
          nr = tunnel.en.R;
          nc = tunnel.en.C;
          nextCost = D[cur.r][cur.c] + tunnel.cost;
          if (D[nr][nc] > nextCost)
          {
            D[nr][nc] = nextCost;
            pq.push({nr, nc, nextCost});
          }
        }
        // en -> st
        if (cur.r == tunnel.en.R && cur.c == tunnel.en.C)
        {
          nr = tunnel.st.R;
          nc = tunnel.st.C;
          nextCost = D[cur.r][cur.c] + tunnel.cost;
          if (D[nr][nc] > nextCost)
          {
            D[nr][nc] = nextCost;
            pq.push({nr, nc, nextCost});
          }
        }
      }
      for (int i = 0; i < 4; i++)
      {
        int nr = cur.r + dr[i];
        int nc = cur.c + dc[i];
        if (nr < 1 || nc < 1 || nr >= N + 1 || nc >= N + 1)
          continue;

        int cost;
        if (board[nr][nc] > board[cur.r][cur.c])
        {
          cost = 2 * (board[nr][nc] - board[cur.r][cur.c]);
        }
        else if (board[nr][nc] == board[cur.r][cur.c])
        {
          cost = 1;
        }
        else
        {
          cost = 0;
        }

        // Relaxation
        // 더 좋은 경로가 생기면 D 갱신하고 큐에 넣기
        nextCost = D[cur.r][cur.c] + cost;
        if (D[nr][nc] > nextCost)
        {
          D[nr][nc] = nextCost;
          pq.push({nr, nc, nextCost});
        }
      }
    }

    cout << "#" << t << " " << D[N][N] << "\n";
  }

  return 0;
}