#include <bits/stdc++.h>
using namespace std;

/*  전략
  1. 인접한 개수 세고 터뜨리는 bfs 로직
  2. 벡터를 사용하여 CbC 이동 및 보드 상태를 CbC 업데이트 */

struct Node {
  int r,c;
  char tag;
};

struct Board {
  char a[12][6];
}; 
bool seen[12][6];
int dr[]={1,0,-1,0};
int dc[]={0,1,0,-1};

bool bfs(Board b, int& popCnt)
{
  queue<Node> q;
  Board backup = b;
  memset(seen, 0, sizeof(seen));
  for(int i=0; i<12;i++)
    for(int j=0; j<6;j++)
    {
      if(b.a[i][j]=='R'||b.a[i][j]=='G'||
          b.a[i][j]=='B'||b.a[i][j]=='P'||b.a[i][j]=='Y'&&seen[i][j]==0)
      {
        seen[i][j]=1;
        q.push({i,j, b.a[i][j]});
        int localCnt = 0;
        while(!q.empty())
        { 
          Node cur = q.front(); q.pop();
          for(int dir=0; dir<4;dir++)
          {
            int nr = cur.r+dr[dir];
            int nc = cur.c+dc[dir];
            if(nr<0||nr>=6||nc<0||nc>=12) continue;
            if(seen[nr][nc] || b.a[nr][nc] != cur.tag) continue;
            seen[nr][nc]=1;
            q.push({nr,nc,cur.tag});
            localCnt++;
            b.a[nr][nc]='X';
          }
        }
        if(localCnt >= 4) 
        {
          popCnt++; 
          return true;
        }
        b = backup;  
      }
    }
  return false;
}

void popX(Board& b)
{
  vector<char> v[6];
  // 1. X를 건너뛰며 삽입
  for(int c=0;c<6;c++)
  {
    for(int r=0;r<12;r++)
      if(b.a[r][c]!='X') v[c].push_back(b.a[c][r]);
    // 2. 패딩 채우기
    while(v[c].size()<12)
      v[c].insert(v[c].begin(), '.');
  }

  for(int c=0;c<6;c++)
    for(int r=0;r<12;r++)
      b.a[c][r] = v[c][r];
}

int main()
{
  Board b;
  for(int i=0; i<12;i++)
  {
    string s;
    cin >> s;
    for(int j=0; j<6;j++)
      s[j] = b.a[i][j];
  }

  // 왜 여기에서 터질까??
  for(int i=0; i<12;i++)
  {
    for(int j=0; j<6;j++)
      cout << b.a[i][j] << " ";
    cout << "\n";
  }
  return 0;
          
  int popCnt = 0;
  // 더이상 터뜨릴게 없을 때까지 반복
  while(bfs(b, popCnt))
  {
    // popNode & 보드상태 변경
    popX(b);
  }

  cout << popCnt;

}