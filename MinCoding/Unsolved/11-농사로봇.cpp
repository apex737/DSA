#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
int board[10][10];
int cpy[10][10];
int cropDay[10][10]; // 파종일

int N, M, mx;
int sum;
struct Pos
{
  int r, c;
};

// 우상좌하
int dc[] = {1, 0, -1, 0};
int dr[] = {0, -1, 0, 1};
int rel_dir[4][4] = {
    {3, 0, 1, 2},
    {0, 1, 2, 3},
    {1, 2, 3, 0},
    {2, 3, 0, 1},
};

void simulate(Pos p, int dir)
{
  int r = p.r;
  int c = p.c;
  int curDir = dir;
  for (int m = 0; m < M; m++)
  {
    // 1. 모든 작물의 성장
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        if (cpy[i][j] > 1 && cpy[i][j] < cropDay[i][j])
        {
          cpy[i][j]++;
        }
      }

    // 2. 오전
    /*
    - 현재 농지가 빈 농지이고 로봇이 다음 농지로 이동할 수 있는 경우 씨를 심는다.
    - 현재 농지가 빈 농지이고, 로봇이 다음 농지로 이동할 수 없을 경우 아무것도 하지 않고 현재 위치에서 머무른다.
    - 현재 농지에 곡식이 열린 경우 수확을 한다. 수확을 하면 농지는 빈 농지가 된다.
    */
    if (cpy[r][c] == 0) // 빈농지
    {
      bool movable = false;
      for (int i = 0; i < 4; i++)
      {
        int nxtDir = rel_dir[curDir][i];
        int nr = r + dr[nxtDir];
        int nc = c + dc[nxtDir];
        if (cpy[nr][nc] == 0 || cpy[nr][nc] == cropDay[nr][nc])
        {
          movable = true;
          break;
        }
      }

      if (movable)
      {
        cpy[r][c] = 2; // 현재위치에 씨 심기
      }
    }

    else if (cpy[r][c] >= cropDay[r][c])
    {
      cpy[r][c] = 0;
      cropDay[r][c]++;
      sum++;
    }
    // 3. 오후
    /* 2) 로봇은 오후에 로봇이 바라보는 방향의 오른쪽, 앞쪽, 왼쪽, 뒤쪽 이웃하는 곳 중, 이동 가능한 곳으로 이동한다.
      - 이동 가능한 곳은 빈 농지, 또는 곡식이 열린 농지이다. 산이거나 싹이 나는 농지인 경우 이동이 불가능하다.
      - 만약, 이동 가능한 곳이 여러 개인 경우, 로봇의 오른쪽, 앞쪽, 왼쪽, 뒤쪽의 순서로 가장 먼저인 이동 가능한 곳으로 이동한다.
      - 만약 이동 가능한 곳이 없는 경우 로봇은 이동하지 않고 현재 위치에 머무른다. */
    for (int i = 0; i < 4; i++)
    {
      int nxtDir = rel_dir[curDir][i];
      int nr = r + dr[nxtDir];
      int nc = c + dc[nxtDir];
      if (cpy[nr][nc] == 0 || cpy[nr][nc] == cropDay[nr][nc])
      {
        // 이동
        r = nr;
        c = nc;
        curDir = nxtDir;
        break;
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
    cin >> N >> M;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        cin >> board[i][j];

    mx = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        if (board[i][j])
          continue;
        for (int dir = 0; dir < 4; dir++)
        {
          sum = 0;
          for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
              cpy[i][j] = board[i][j];

          for (int k = 0; k < N; k++)
            for (int p = 0; p < N; p++)
              cropDay[k][p] = 7; // 첫번째로 싹이난경우
          simulate({i, j}, dir);
          mx = max(mx, sum);
          // 초기화
        }
      }
    cout << "#" << t << " " << mx << "\n";
  }
}