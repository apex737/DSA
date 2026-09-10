#include <iostream>
#include <queue>
#include <cstring>

/*  북극곰

전략

1. 상하좌우 스캔해서 최초 adj 배열 생성
2. 매년마다...
1) 빙하높이 갱신
2) adj 배열도 갱신
3) FF로 두 구역이 분리되었는지 검증
=> 최초 시드에 연결된 덩어리에 방문표식을 남겼는데,
=> 그 이후로 !visited가 하나라도 발견된다면 break

*/
using namespace std;

int board[80][80];
int visited[80][80];
int adj[80][80];

struct Pos
{
  int r, c;
};

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int N, M;

void updateAdj(int i, int j)
{
  int adjCnt = 0;
  for (int dir = 0; dir < 4; dir++)
  {
    int nr = i + dr[dir];
    int nc = j + dc[dir];
    if (board[nr][nc] == 0)
      adjCnt++;
  }
  adj[i][j] = adjCnt;
}

int main()
{
  cin >> N >> M;
  memset(adj, -1, sizeof(adj));
  // 1. 상하좌우 스캔해서 adj 배열 생성
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
    {
      cin >> board[i][j];
    }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
    {
      if (board[i][j] > 0)
      {
        updateAdj(i, j);
      }
    }

  int ans = 0;
  for (int year = 1; year <= M; year++)
  /* 매년마다..
      1) 빙하높이 갱신
      2) adj 배열도 갱신
      3) FF로 두 구역이 분리되었는지 검증
      => 최초 시드에 연결된 덩어리에 방문표식을 남겼는데,
      => 그 이후로 !visited가 하나라도 발견된다면 break
  */
  {
    // 1) 빙하 수명 차감
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
      {
        if (board[i][j] > 0)
        {
          board[i][j] -= adj[i][j];
          if (board[i][j] <= 0) // 빙하소멸
          {
            board[i][j] = 0; // 바다로 만들기
            adj[i][j] = -1;
          }
        }
      }

    // 2) adj 갱신
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
      {
        if (board[i][j] > 0)
          updateAdj(i, j);
      }

    // 3) FF로 두 구역이 분리되었는지 검증
    bool firstFill = true;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
      {
        if (board[i][j] > 0)
        {
          // 이미 플러드필을 했는데 방문표식이 안찍혀있다?
          // => 분리되어있다.
          if (!firstFill && !visited[i][j])
          {
            ans = year;
            goto EXIT;
          }

          else // BFS-FF
          {
            queue<Pos> q;
            q.push({i, j});
            visited[i][j] = 1;
            while (!q.empty())
            {
              auto cur = q.front();
              q.pop();
              for (int dir = 0; dir < 4; dir++)
              {
                int nr = cur.r + dr[dir];
                int nc = cur.c + dc[dir];
                if (visited[nr][nc])
                  continue;
                if (!board[nr][nc])
                  continue;
                visited[nr][nc] = 1;
                q.push({nr, nc});
              }
            }

            firstFill = false;
          }
        }
      }

    // 4) visited 초기화
    memset(visited, 0, sizeof(visited));
  }

EXIT:
  cout << ans << "\n";
}