#include <bits/stdc++.h>

using namespace std;

int dr[]={1,0,-1,0};
int dc[]={0,1,0,-1};
// F for fence : 시작좌표로 구성
bool fence[1001][1001]; // F for Fence
bool seen[1001][1001]; // S for Seen
struct Node {
  int r,c,d;
};
int cnt;
int main()
{
  int M, N, K;
  cin >> M >> N >> K;
  Node start, end;
  while(K--)
  {
    cin >> start.r >> start.c;
    cin >> end.r >> end.c;
    for(int i = start.r; i < end.r; i++)
      for(int j = start.c; j < end.c; j++)
        fence[i][j]=1;
  }

  // BFS Standard Form
  queue<Node> q;
  vector<int> area;
  // 1. Full Search를 하되
  for(int i = 0; i < M; i++)
    for(int j = 0; j < N; j++)
    {
      // 2. 방문한적도 없고, 장애물도 아닌것만
      if(seen[i][j]==0 && fence[i][j]==0)
      {
        seen[i][j]=1; // 플래그 소비
        q.push({i,j,0});
        while(1)
        {
          // 나가기전에 어떻게 최대 dist를남길것인지??
          Node cur = q.front(); q.pop();
          for(int i = 0; i < 4; i++)
          {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            if(nr<0||nr>=N||nc<0||nc>=M) continue;
            if(seen[nr][nc] || fence[nr][nc]) continue;
            seen[nr][nc]=1;
            q.push({nr,nc,cur.d+1});
          }
        }
        // 하나의 영역이 종료됨 
        cnt++;

      }
    }


}