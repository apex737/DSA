#include <bits/stdc++.h>
using namespace std;

int N,M,H; // 100
int board[101][101][101];
bool seen [101][101][101];
struct Node {
  int z,r,c,d;
};

// Def mov cmd
int dr[]={1,0,-1,0,0,0};  
int dc[]={0,1,0,-1,0,0};
int dz[]={0,0,0,0,1,-1};
int maxD;
int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> M >> N >> H;
  queue<Node> q;
  for(int k = 0; k < H; k++)
  {
    for(int i=0;i<N;i++)
      for(int j=0;j<M;j++)
      {
        cin >> board[k][i][j];
        if(board[k][i][j]==1) {
          q.push({k,i,j,0});
          seen[k][i][j]=1;
        }
      }
  }

  // 위아래 전이는 z축에서 같은 위치로 전파
  while(!q.empty())
  {
    Node cur = q.front(); q.pop();
    maxD = max(maxD, cur.d);
    for(int i=0;i<6;i++)
    {
      int nz = cur.z+dz[i];
      int nr = cur.r+dr[i];
      int nc = cur.c+dc[i];
      /*Check B, F, S*/
      // 1. Bound
      if(nr<0||nr>=N||nc<0||nc>=M||nz<0||nz>=H) continue;
      // 2. Fence, Seen
      if(board[nz][nr][nc]==-1 || seen[nz][nr][nc]) continue;
      // Update 
      seen[nz][nr][nc]=1;
      board[nz][nr][nc]=1;
      q.push({nz,nr,nc,cur.d+1});
    }
  }

  for(int k=0;k<H;k++)
    for(int i=0;i<N;i++)
      for(int j=0;j<M;j++)
      {
        if(board[k][i][j]==0) 
        {
          cout << -1 << "\n";
          return 0;
        }  
      }
  cout << maxD << "\n";
  return 0;
}