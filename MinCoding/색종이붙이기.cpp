#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
  int r, c;
};

int papers[6];
int T;
int board[14][14];
vector<Pair> pairs;
int mn;

void dfs(int idx, int cnt);
bool check(Pair p, int w);

int main()
{
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    mn = 999;
    pairs.clear(); 
    std::fill(papers, papers + 6, 5); // 5로 초기화
    
    for (int i = 0; i < 10; i++)
      for (int j = 0; j < 10; j++)
      {
        cin >> board[i][j];
        if (board[i][j] == 1)
          pairs.push_back({i, j});
      }

    dfs(0, 0);
    if(mn == 999) mn = -1;
    cout << "#" << t << " " << mn << "\n";
  }
  return 0;
}

void dfs(int idx, int cnt)
{
  // pruning: 이미 최소값보다 많이 사용했다면 더 볼 필요 없음
  if (cnt >= mn) return; 

  // D epth: pair를 전부 확인
  if(idx == pairs.size()) {
    mn = min(mn, cnt);
    return;
  }

  // F ork: 노드마다 (1x1 ~ 5x5) 시도
  auto p = pairs[idx];

  // S een: 보드가 이미 마킹된 상태 => 다음으로 
  if(board[p.r][p.c] == 0) dfs(idx+1, cnt);
  else 
  {
    for(int w=1; w<=5; w++) 
    {
      if(papers[w] > 0 && check(p, w)) 
      {
        for(int i=0; i<w; i++)
          for(int j=0; j<w; j++)
            board[p.r+i][p.c+j] = 0; 
        papers[w]--;
        
        dfs(idx+1, cnt+1);
        
        papers[w]++;
        for(int i=0; i<w; i++)
          for(int j=0; j<w; j++)
            board[p.r+i][p.c+j] = 1; 
      }
    }
  }
}

bool check(Pair p, int w)
{
  for(int i=0; i<w; i++)
    for(int j=0; j<w; j++)
    {
      int nr = p.r+i;
      int nc = p.c+j;
      if(nr>=10 || nc>=10 || !board[nr][nc]) return false;
    }
  return true;
}