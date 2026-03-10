#include <bits/stdc++.h>

using namespace std;

// 일반적 bfs와 다르게 이건 x,y 좌표계를 쓰네
// (노드의 전파 횟수 + 1) 이 곧 넓이니까 루프에서 카운터만 돌려주면 그게 넓이겠네
// 1. 먼저 fence 받아서 보드에 표시하고
// 2. 각 직사각형마다 bfs 카운터 돌린다음
// 3. 벡터에 넣어서 정렬하면 끝?
int board[101][101];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
struct Node {
  int x,y;
};
int main()
{
  int M, N, K;
  cin >> M >> N >> K;
  Node start, end;
  while(K--)
  {
    // 1. 먼저 fence 받아서 보드에 표시
    cin >> start.x >> start.y;
    cin >> end.x >> end.y;
    for(int i = start.x; i < end.x; i++)
      for(int j = start.y; j < end.y; j++)
        board[i][j]=-1;
  }

  // 2. 각 직사각형마다 bfs 카운터 돌리기
  // + 추가로, 개별 직사각형에 대해서도 돌려야함
  
  queue<Node> q;
  vector<int> areas;
  int areaCnt = 0;
  // BFS Standard Form & Full Search
  for(int i=0;i<N;i++)
    for(int j=0;j<M;j++)
    {
      if(board[i][j]!=-1 && board[i][j]==0)
      {
        areaCnt++; board[i][j]=1; 
        q.push({i,j});
        int area=1;
        while(!q.empty())
        {
          Node cur = q.front(); q.pop();
          for(int i=0;i<4;i++)
          {
            int nx = cur.x+dx[i];
            int ny = cur.y+dy[i];
            if(nx<0||nx>=N||ny<0||ny>=M) continue;
            if(board[nx][ny]!=0) continue;
            board[nx][ny]=1;
            q.push({nx,ny});
            area++;
          }
        }
        areas.push_back(area);
      } 
    }
  // 3. 벡터에 넣어서 정렬하면 끝  
  sort(areas.begin(), areas.end());
  cout << areaCnt << "\n";

  for(int area : areas) cout << area << " ";
}