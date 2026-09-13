#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <tuple>
#include <functional>

using namespace std;

const int INF = 1e9;

/*
전략

1. BFS Flood Fill로 각 부품에 ID 지정
2. 부품 간 직선 케이블 길이를 cost[][]에 저장
3. cost[][]를 인접리스트로 변환
4. Prim MST로 모든 부품을 최소 비용으로 연결
*/

int board[11][11];
int visited[11][11];

// cost[u][v] : u번 부품과 v번 부품을
// "직접" 연결할 수 있는 최소 케이블 길이
int cost[11][11];

struct Pos
{
  int r, c;
};

// 우 하 좌 상
int dc[] = {1, 0, -1, 0};
int dr[] = {0, 1, 0, -1};

int N, M;

bool OOB(int r, int c)
{
  return r < 0 || c < 0 || r >= N || c >= M;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;

  memset(visited, 0, sizeof(visited));

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      cin >> board[i][j];

  // =========================================================
  // 1. BFS Flood Fill
  // =========================================================

  int id = 1;

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      if (!board[i][j] || visited[i][j])
        continue;

      queue<Pos> q;

      visited[i][j] = 1;

      // ★ [BUG FIX 1]
      // 시작점도 현재 부품 ID로 반드시 바꿔야 한다.
      board[i][j] = id;

      q.push({i, j});

      while (!q.empty())
      {
        auto cur = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++)
        {
          int nr = cur.r + dr[dir];
          int nc = cur.c + dc[dir];

          if (OOB(nr, nc))
            continue;

          if (visited[nr][nc])
            continue;

          // ★ [BUG FIX 2]
          // 기존 코드에는 이 검사가 없어서
          // 0인 바다까지 Flood Fill 해버렸다.
          if (board[nr][nc] == 0)
            continue;

          visited[nr][nc] = 1;
          board[nr][nc] = id;

          q.push({nr, nc});
        }
      }

      id++;
    }
  }

  // 실제 부품 개수
  int V = id - 1;

  // =========================================================
  // 2. 부품 간 직선 케이블 비용 계산
  // =========================================================

  for (int i = 1; i <= V; i++)
  {
    for (int j = 1; j <= V; j++)
    {
      if (i == j)
        cost[i][j] = 0;
      else
        cost[i][j] = INF;
    }
  }

  /*
      모든 부품 칸에서 4방향으로 직선을 쏜다.

      0을 만남      -> 계속 진행
      같은 ID       -> 실패
      다른 ID       -> 거리 계산
      OOB           -> 실패

      케이블 길이는 빈칸 개수.
      문제 조건상 길이 1은 불가능.
  */

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      int cur = board[i][j];

      if (cur == 0)
        continue;

      for (int dir = 0; dir < 4; dir++)
      {
        for (int d = 1;; d++)
        {
          int nr = i + dr[dir] * d;
          int nc = j + dc[dir] * d;

          // ★ [BUG FIX 3]
          // 반드시 배열 접근보다 OOB 검사를 먼저 해야 한다.
          if (OOB(nr, nc))
            break;

          int nxt = board[nr][nc];

          // 빈칸이면 계속 직진
          if (nxt == 0)
            continue;

          // 같은 부품을 만나면 이 방향은 실패
          if (cur == nxt)
            break;

          // 다른 부품 발견
          // d는 두 부품 칸 사이 좌표 차이
          // 실제 케이블 길이는 빈칸 개수 = d - 1
          int len = d - 1;

          // 문제 조건 : 길이 1 케이블 금지
          if (len >= 2)
          {
            cost[cur][nxt] =
                min(cost[cur][nxt], len);

            // 양방향 간선
            cost[nxt][cur] =
                min(cost[nxt][cur], len);
          }

          // 다른 부품을 만났으니 더 뒤는 볼 필요 없음
          break;
        }
      }
    }
  }

  // =========================================================
  // 3. cost[][] -> 인접 리스트
  // =========================================================

  // adj[u] = {비용, 도착 정점}
  vector<pair<int, int>> adj[11];

  for (int u = 1; u <= V; u++)
  {
    // u < v만 확인해서 중복 방지
    for (int v = u + 1; v <= V; v++)
    {
      if (cost[u][v] == INF)
        continue;

      adj[u].push_back({cost[u][v], v});
      adj[v].push_back({cost[u][v], u});
    }
  }

  // =========================================================
  // 4. Prim MST
  // 강의 스타일
  // =========================================================

  // chk[i] : i번 정점이 MST에 들어왔는가?
  bool chk[11] = {false};

  // 선택된 MST 간선 개수
  int cnt = 0;

  // MST 총 비용
  int ans = 0;

  /*
      {비용, 출발 정점, 도착 정점}

      비용이 가장 작은 간선이 top에 오도록 최소힙
  */
  priority_queue<
      tuple<int, int, int>,
      vector<tuple<int, int, int>>,
      greater<tuple<int, int, int>>>
      pq;

  // 시작 정점 1을 MST에 포함
  chk[1] = true;

  // 1번 정점에서 나가는 모든 간선을 PQ에 삽입
  for (auto nxt : adj[1])
  {
    int w = nxt.first;
    int v = nxt.second;

    pq.push({w, 1, v});
  }

  /*
      정점 V개짜리 MST는
      간선 V-1개를 선택하면 완성된다.
  */
  while (cnt < V - 1)
  {
    // ★ [BUG FIX 4]
    // 연결 불가능한 그래프라면 PQ가 먼저 비게 된다.
    if (pq.empty())
    {
      ans = -1;
      break;
    }

    auto [w, a, b] = pq.top();
    pq.pop();

    /*
        ★ [BUG FIX 5] 매우 중요

        기존 코드에서는 PQ에 넣는 순간
        visited 처리하려고 했는데,
        Prim에서는 그러면 안 된다.

        같은 b로 가는 후보가 여러 개 있을 수 있고,
        그중 "가장 싼 간선"이 나중에 PQ에서 뽑혀야 한다.

        따라서 방문 처리는 PUSH가 아니라
        POP 후 실제 간선을 채택하는 순간 한다.
    */
    if (chk[b])
      continue;

    // 이 간선을 MST에 채택
    chk[b] = true;
    ans += w;
    cnt++;

    // 새로 MST에 들어온 b에서 나가는 간선들을 PQ에 추가
    for (auto nxt : adj[b])
    {
      int nw = nxt.first;
      int nv = nxt.second;

      if (chk[nv])
        continue;

      pq.push({nw, b, nv});
    }
  }

  cout << ans << '\n';

  return 0;
}