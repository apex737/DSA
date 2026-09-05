/* 다익스트라는 BFS Queue 패턴과 유사하지만
  1. 큐 대신 최소힙을 사용
  2. visited를 D-table이 자체적으로 대체 (lazy-deletion)


*/


#include <bits/stdc++.h>
using namespace std;

// 상 / 하 / 좌 / 우
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct Edge {
  int r,c,cost;
};

// 최소힙 특징이라고 봐도 되나? 더 크면 가라앉는다?
// 템플릿 보면 greater<Edge> 같은거 넘기던데?
// 왜 구조체로 감싸는걸까?
struct cmp
{
  bool operator()(Edge a, Edge b)
  {
    return a.cost > b.cost;
  }
};

// int visited[33][33];
int h[33][33];
int D[33][33]; // u -> v 비용

int main()
{
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++)
  {
    int N;
    cin >> N;

    // 1. 지도 입력
    for(int i=1; i<=N; i++)
      for(int j=1; j<=N; j++)
        cin >> h[i][j];

    // 2. 최단거리 테이블 초기화
    for(int i=1; i<=N; i++)
      for(int j=1; j<=N; j++)
        D[i][j] = 1e9;
    D[1][1]=0;

    // 3. 최소 힙
    // 누적비용이 가장 싼 정점을 먼저 꺼낸다.
    priority_queue<Edge, vector<Edge>, cmp> pq;
    pq.push({1,1,0});

    // 4. 다익스트라
    while (!pq.empty())
    {
      Edge cur = pq.top(); pq.pop(); 
      if(cur.r == N && cur.c == N) break;
      // 비싼경로 무시
      if(D[cur.r][cur.c] < cur.cost) continue;

      for (int i = 0; i < 4; i++)
      {
        int nr = cur.r + dr[i];
        int nc = cur.c + dc[i];
        if(nr<1||nc<1||nr>=N+1||nc>=N+1) continue;
        int cost;
        // 세 가지 규칙에 따라 cost 계산
        int curH = h[cur.r][cur.c];
        int nxtH = h[nr][nc];
        cost = nxtH < curH ? 0 : nxtH == curH ? 1 : 2*(nxtH-curH); 
        
        // Relaxation(완화)
        int nextCost = cost + cur.cost;
        if (nextCost < D[nr][nc])
        {
          D[nr][nc] = nextCost;
          pq.push({nr,nc,nextCost});
        }
      }
    }

    cout << "#" << tc << " " << D[N][N] << "\n";
  }

  return 0;
}