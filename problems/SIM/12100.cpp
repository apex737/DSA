#include <bits/stdc++.h>
using namespace std;

/* 노드의 이동방식과 보드의 위치가 정의되어있다..
- 전형적인 BFS 아닌가? 
- 그러면 진짜로 큐 패턴을 써야할까? 
: Yes. 그래야 모든 노드를 공평하게 이동시킬수 있으니까
- 하지만 이동에는 순서가 존재하기 때문에 그걸 컨트롤하는게 핵심인듯? */
// 방향에 맞게 루프를 돌며 한 줄씩 처리

// mov 상하좌우: 엣지로 전부이동
// 가능하면 merge -> 벽에다 짜부

// 
int n;
int maxVal;
struct Board {
  int a[21][21];
};

Board b;
vector<int> compressLine(const vector<int> line);
void dfs(int cur, Board b);
Board mov(const Board& b, int dir);

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
  int size = (int)line.size();
  for(int x : line)
    if(x!=0) v.push_back(x);
  // 2. 합칠수있으면 합치기
  // 4 4 2; 인접한게 같으면 합침
  for(int i = 0; i < v.size(); i++)
  {
    if(i+1<v.size() && v[i]==v[i+1]) // 쇼트서킷룰
    {
      v[i]+=v[i+1];
      v[i+1]=0;
    }
  }
  // 3. 마저 밀어주고 남은자리 0 패딩
  int padding = size-v.size();
  for(int i = 0; i < v.size(); i++)
  {
    if(v[i]==0 && i+1 < v.size()){
      v[i] = v[i+1];
      v[i+1]=0;
    }
  }
  while(padding--)
    v.push_back(0);
  return v;
}

Board mov(const Board& b, int dir)
{
  Board ret;
  // cbc, rbr을 구별해야할까? 결과는 행렬인데..
  switch (dir)
  {
    case 0: {
      // 먼저 b의 한 라인을 넘겨서 옮긴다.
      vector<int> line;
      for(int c=0;c<n;c++)  // col by col로 움직이면서 벡터삽입
      {
        for(int r=0;r<n;r++)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int r=0;r<n;r++)
          ret.a[r][c]= line[r];
      }
      break;
    }
    case 1: {
      vector<int> line;
      for(int c=0;c<n;c++)  // CbC로 움직이면서 벡터삽입
      {
        for(int r=n-1;r>=0;r--)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int r=n-1;r>=0;r--)
          ret.a[r][c]= line[r];
      }
      break;
    }
    case 2: {
      vector<int> line;
      for(int r=0;r<n;r++)  // RbR로 움직이면서 벡터삽입
      {
        for(int c=0;c<n;c++)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int c=0;c<n;c++)
          ret.a[r][c]= line[r];
      }
      break;
    }
    case 3: {
      vector<int> line;
      for(int r=0;r<n;r++)  // RbR로 움직이면서 벡터삽입
      {
        for(int c=n-1;c>=0;c--)
          line.push_back(b.a[r][c]);       
        line = compressLine(line);
        for(int c=n-1;c>=0;c--)
          ret.a[r][c]= line[r];
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