#include <bits/stdc++.h>
using namespace std;

int dr[]={1,0,-1,0};
int dc[]={0,1,0,-1};
int n;
int board[30][30];
bool seen[30][30];
struct Node {
  int r,c;
};
int no=0;
int cnt;
int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  string s; // 입력이 붙어서 오는 경우 표준해법
  for(int i=0;i<n;i++)  
  {
    cin >> s; 
    for(int j=0;j<n;j++)
      board[i][j] = s[j]-'0';
  }

  queue<Node> q; 
  vector<int> v;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(board[i][j]==1&&seen[i][j]==0)
      {
        cnt=1;
        q.push({i,j});
        seen[i][j]=1;
        no++;
        while(!q.empty())  
        {
          Node cur = q.front(); q.pop();
          for(int i=0;i<4;i++)
          {
            int nr=cur.r+dr[i];
            int nc=cur.c+dc[i];
            if(nr<0||nr>=n||nc<0||nc>=n) continue;
            if(board[nr][nc]==0||seen[nr][nc]) continue;
            seen[nr][nc]=1;
            board[nr][nc]=no;
            q.push({nr,nc});
            cnt++;
          }
        }
        v.push_back(cnt);
      }
    }
  }
  sort(v.begin(), v.end());
  cout << no << "\n";
  for(int num : v) cout << num << "\n";
}