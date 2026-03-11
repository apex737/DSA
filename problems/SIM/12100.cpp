#include <bits/stdc++.h>
using namespace std;

int n;
int maxVal;
struct Board {
  int a[21][21];
};

Board b;
vector<int> compressLine(const vector<int> line);
void dfs(int cur, Board b);
Board mov(const Board& b, int dir);

/* 
  1. 일반적으로, 메모리 사용은 문제를 단순화한다.
  2. dfs 인자로 그리드(보드) 구조체를 넘기는 패턴이 존재한다.
  3. 문제가 복잡하면 (여러 함수로) 쪼개라.
  4. 쇼트서킷 룰로 세그폴트 리스크를 헤지할 수 있다. 
*/

int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) 
      cin >> b.a[i][j];
  
  dfs(0, b);
  cout << maxVal;
}

/* 커맨드에 따라 보드배치를 바꾸고 mx를 업데이트 */
// 한번에 다 하려고 하지말고 함수로 분리 
// 벡터의 장점은 형태에 대해 자유롭다는 점이다
vector<int> compressLine(const vector<int> line)
{
  // 1. 벡터에 전부 넣기
  vector<int> v;
  vector<int> ret; // 메모리를 더 쓸 수록 문제가 간단해질 확률이 높아진다. 
  for(int x : line)
    if(x!=0) v.push_back(x);

  // 2. 합칠수있으면 합치기
  for(int i = 0; i < v.size(); i++)
  {
    if(i+1<v.size() && v[i]==v[i+1]) { // tip: 쇼트서킷룰
      ret.push_back(v[i]*2);
      i++;
    }
    else ret.push_back(v[i]);
  }
  
  // 3. 남은자리 0 패딩; 메모리를 더 썼더니 문제가 사라졌다.
  while(ret.size() < n) ret.push_back(0); // 피드백 루프

  return ret;
}

Board mov(const Board& b, int dir)
{
  Board ret;
  switch (dir)
  {
    case 0: {
      for(int c=0;c<n;c++)  // Col by Col로 움직이면서 벡터삽입
      {
        vector<int> line;
        for(int r=0;r<n;r++)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int r=0;r<n;r++)
          ret.a[r][c]= line[r];
      }
      break;
    }
    case 1: {
      for(int c=0;c<n;c++)  // CbC로 움직이면서 벡터삽입
      {
        vector<int> line;
        for(int r=n-1;r>=0;r--)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int r=n-1, i=0;r>=0;r--,i++)
          ret.a[r][c]= line[i]; // 역순 삽입
      }
      break;
    }
    case 2: {
      for(int r=0;r<n;r++)  // RbR로 움직이면서 벡터삽입
      {
        vector<int> line;
        for(int c=0;c<n;c++)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int c=0;c<n;c++)
          ret.a[r][c]= line[c];
      }
      break;
    }
    case 3: {
      for(int r=0;r<n;r++)  // RbR로 움직이면서 벡터삽입
      {
        vector<int> line;
        for(int c=n-1;c>=0;c--)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int c=n-1,i=0;c>=0;c--,i++)
          ret.a[r][c]= line[i]; // 역순 삽입
      }
      break;
    }
  }
   return ret;
}

int getMax(const Board& b)
{
  int mx=0;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      mx = max(mx, b.a[i][j]);
  return mx;
}

void dfs(int cur, Board b)
{
  if(cur==5) {
    maxVal = max(maxVal, getMax(b));
    return;
  }

  for(int dir = 0; dir < 4; dir++)  // 상하좌우 
  {
    Board nxt = mov(b, dir);
    dfs(cur+1, nxt);
  }
} 