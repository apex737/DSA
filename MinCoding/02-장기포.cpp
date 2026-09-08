#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int ans;
int N;
int board[51][51];
// 마지막에 마킹된 쫄로 리턴
int eaten[51][51];
int mx;
struct Pos
{
  int r, c;
};
// 우상좌하
int dc[] = {1, 0, -1, 0};
int dr[] = {0, -1, 0, 1};

void dfs(int cur, Pos piv)
{
  if (cur == 3)
  {
    return;
  }

  // 4방향 보면서 쫄 위치확인 & 그 다음부터가 다음 착수 위치
  for (int i = 0; i < 4; i++)
  {
    int nr, nc, d;
    bool found = false;
    /* 무한루프에서는 하나의 태스크만 수행하고 완료가 되자마자 break
      태스크 완료 상태는 플래그로 관리 */

    // 무한루프 1. 첫번째 쫄 찾기
    for (d = 1;; d++)
    {
      nr = piv.r + dr[i] * d;
      nc = piv.c + dc[i] * d;
      if (nr < 0 || nc < 0 || nr >= N || nc >= N)
        break;

      if (board[nr][nc] == 1) // 첫번째 쫄을 찾음
      {
        found = true;
        break;
      }
    }

    if (!found)
      continue;

    // 무한루프 2. 빈칸이나 두번째 쫄을 만나면 DFS
    for (int dd = d + 1;; dd++)
    {
      nr = piv.r + dr[i] * dd;
      nc = piv.c + dc[i] * dd;
      if (nr < 0 || nc < 0 || nr >= N || nc >= N)
        break;

      if (board[nr][nc] == 1)
      {
        eaten[nr][nc] = 1;
        board[nr][nc] = 0;
        dfs(cur + 1, {nr, nc});
        board[nr][nc] = 1;
        break; // 두번째 쫄이 상한
      }

      else
      {
        dfs(cur + 1, {nr, nc});
        // break;  -> 빈칸 스캔은 필요하니까 여기는 break 안함
      }
    }
  }
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N;
    ans = 0;
    Pos st;
    memset(eaten, 0, sizeof(eaten));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        cin >> board[i][j];
        if (board[i][j] == 2)
        {
          st.r = i;
          st.c = j;
        }
      }
    dfs(0, st);
    int sum = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        sum += eaten[i][j];
    cout << "#" << t << " " << sum << "\n";
  }
  return 0;
}