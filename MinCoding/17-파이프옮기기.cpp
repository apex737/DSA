#include <iostream>

using namespace std;

struct Pos
{
  int r, c;
};
struct Pipe
{
  Pos st, en; // 시작,끝점
  int state;  // 0: 가로, 1: 세로, 2: 대각선
};

int N, cnt;
int board[20][20];
void dfs(Pipe p);
bool checkDiag(const Pos &p);
int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N;
    cnt = 0;
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        cin >> board[i][j];

    Pipe p{{1, 1}, {1, 2}, 0};

    /* 전략
      매번 state 별로 2개 또는 3가지 경우의 수로 p를 변경한다.
      en이 N, N에 도달할 때까지 계속하는 DFS
    */

    dfs(p);

    cout << "#" << t << " " << cnt << "\n";
  }
  return 0;
}

void dfs(Pipe p)
{
  // 범위 이탈시 리턴
  if (p.en.r > N || p.en.c > N)
    return;

  // 벽만나면 리턴
  if (board[p.en.r][p.en.c])
    return;

  if (p.en.r == N && p.en.c == N)
  {
    cnt++;
    return;
  }

  // 2개 또는 3가지 fork
  switch (p.state)
  {
  case 0:
    if (!board[p.en.r][p.en.c + 1])
      dfs({p.en, {p.en.r, p.en.c + 1}, 0}); // 가로
    if (checkDiag(p.en))
      dfs({p.en, {p.en.r + 1, p.en.c + 1}, 2}); // 대각선
    break;
  case 1:
    if (!board[p.en.r + 1][p.en.c])
      dfs({p.en, {p.en.r + 1, p.en.c}, 1}); // 세로
    if (checkDiag(p.en))
      dfs({p.en, {p.en.r + 1, p.en.c + 1}, 2}); // 대각선
    break;
  case 2:
    if (!board[p.en.r][p.en.c + 1])
      dfs({p.en, {p.en.r, p.en.c + 1}, 0}); // 가로
    if (!board[p.en.r + 1][p.en.c])
      dfs({p.en, {p.en.r + 1, p.en.c}, 1}); // 세로
    if (checkDiag(p.en))
      dfs({p.en, {p.en.r + 1, p.en.c + 1}, 2}); // 대각선
    break;
  }
}

bool checkDiag(const Pos &p)
{
  if (board[p.r][p.c] || board[p.r][p.c + 1] ||
      board[p.r + 1][p.c] || board[p.r + 1][p.c + 1])
    return false;
  return true;
}