#include <bits/stdc++.h>
using namespace std;

/*  전략
  1. 보드를 받되, 최댓값을 찾는다
  2. 최댓값까지 for 루프를 돌면서 영역의 수를 찾는다.
  3. 영역의 수는 full-search를 한다
  4. bfs 표준형에서 fence를 장마 LV 이하의 값들로 한다 */

int n;
int maxCnt;  
int board[101][101];
bool seen[101][101];
int dr[]={1,0,-1,0};
int dc[]={0,1,0,-1};
struct Node {
  int r,c;
};

int main()
{
  cin >> n;
  // 1. 보드를 받되, 최댓값을 찾는다
  int mx=0;  
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    {
      cin >> board[i][j];
      mx=max(mx, board[i][j]);
    }
  queue<Node> q;
  // 2. 최댓값까지 for 루프를 돌면서 영역의 수를 찾는다.
  for(int rainLV=2;rainLV<mx;rainLV++) // 장마의 레벨은 2 ~ mx-1 까지이며, 레벨 이하는 fence로 간주한다
  {
    int localCnt = 0; 
    memset(seen, 0, sizeof(seen));
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {
        if(board[i][j]>rainLV && seen[i][j]==0)
        {
          seen[i][j]=1;
          q.push({i,j});
          localCnt++;
          while(!q.empty())
          {
            Node cur = q.front(); q.pop();
            for(int dir=0; dir<4; dir++)
            {
              int nr = cur.r+dr[dir];
              int nc = cur.c+dc[dir];
              if(nr<0||nr>=n||nc<0||nc>=n) continue;
              if(board[nr][nc]<=rainLV || seen[nr][nc]) continue;
              seen[nr][nc]=1;
              q.push({nr,nc});
            }
          }
        }
      }
    }
    maxCnt = max(maxCnt, localCnt);
  }
  cout << maxCnt;

}