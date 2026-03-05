#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct CCTV { int r, c, type; };
int N, M, min_blind = 64;
vector<CCTV> cctvs;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

// 벡터로 서로 다른 이동방식 정의
vector<vector<int>> mov[6] = {
    {},
    {{0}, {1}, {2}, {3}}, 
    {{0, 2}, {1, 3}}, 
    {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, 
    {{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}}, 
    {{0, 1, 2, 3}}
};

// 한 방향으로 쭉 칠하는 함수
void fill_watch(int board[8][8], int r, int c, int dir) 
{
  int nx = r, ny = c;
  while (1) 
  {
    nx += dx[dir]; ny += dy[dir];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M || board[nx][ny] == 6) break;
    if (board[nx][ny] == 0) board[nx][ny] = -1; // 감시 구역 표시
  }
}

/*  처음생각: DFS를 한다는건 결국 4가지 방향중에서 최적의 한가지 방향을 결정하고
    나머지 방향을 포기하고 상위 노드로 돌아오는것?? */
void dfs(int idx, int board[8][8]) 
{
  // 1. 기저 조건: 모든 CCTV 다 돌았으면 사각지대 계산
  if (idx == cctvs.size()) 
  {
      int cnt = 0;
      for (int i = 0; i < N; i++)
          for (int j = 0; j < M; j++) 
            if (board[i][j] == 0) cnt++;
      min_blind = std::min(min_blind, cnt);
      return;
  }

  CCTV cur = cctvs[idx];
  
  // 2. 현재 CCTV의 가능한 모든 회전 방향을 시도
  for (auto& dirs : mov[cur.type]) 
  {
      int temp[8][8]; // 복사본을 만듦 (백트래킹의 핵심)
      for (int i = 0; i < N; i++)
          for (int j = 0; j < M; j++) temp[i][j] = board[i][j];

      // 3. 복사본에 감시 영역 표시
      for (int dir : dirs) 
          fill_watch(temp, cur.r, cur.c, dir);

      // 4. 다음 CCTV로 재귀 호출
      dfs(idx + 1, temp);
  }
}

int main() 
{
  int first[8][8];
  cin >> N >> M;
  for (int i = 0; i < N; i++) 
  {
      for (int j = 0; j < M; j++) 
      {
          cin >> first[i][j];
          if (first[i][j] >= 1 && first[i][j] <= 5)
            cctvs.push_back({i, j, first[i][j]});
      }
  }

  dfs(0, first);
  cout << min_blind;
  return 0;
}