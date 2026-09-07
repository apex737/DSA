#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int M; // 개척자의 잔류기간
// 전략: 완전탐색 + BFS

// 가장 많이 수확할 수 있는 시작 위치와 방향

// 오른쪽, 앞쪽, 왼쪽, 뒤쪽의 순서
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
int board[10][10];
int cpyBoard[10][10];
int mx;

struct Pos
{
  int r, c, dir;
};

// 시뮬레이션,,
/* BFS 정규형인 큐를 쓸지 벡터를 쓸지 고민중
vector<Seed>를 써야겠다고 생각함.
Seed 피드백 패턴은 원자시뮬레이션에서도 사용..
중복방문이 가능해서 visited는 의미가 없다.
*/

struct Seed
{
  int r, c;
  int t; // 시드별 날짜
};

int bfs(Pos st)
{
  // Seed 피드백 패턴 시작
  /* 핵심 cur -> nxt로 seed를 넘겨주면서
      1. 시드의 상태와
      2. 보드의 상태와
      3. Head의 위치를
      시뮬레이션 하기
  */
  int nr, nc, r, c, dir;
  int cnt = 0;
  r = st.r;
  c = st.c;
  dir = st.dir;
  vector<Seed> cur;
  bool canMove = true;
  for (int m = 0; m < M; m++)
  /*
      board==0: 빈칸
      board==1: 산
      board==2: 작물/씨앗
      board==3: 수확가능
  */
  {

    // 1. 씨를 뿌리고 작물 상태를 업데이트
    vector<Seed> nxt;
    if (canMove)
    {
      cpyBoard[r][c] = 2;
      cur.push_back({r, c, -1});
    }
    for (Seed s : cur)
    {
      if (++s.t > 3)
      {
        cpyBoard[s.r][s.c] = 3; //
      }
      nxt.push_back(s);
    }
    // 2. 이동 가능한 방향으로 바꾼다
    // 4방향 다 돌렸는데 안되면 그냥 막힌거다.
    canMove = false;
    for (int i = 0; i < 4; i++)
    {
      nr = r + dr[dir];
      nc = c + dc[dir];
      if ((cpyBoard[nr][nc] == 1 || cpyBoard[nr][nc] == 2)
          /* || (nr < 0 || nc < 0 || nr >= N || nc >= N) */)
      {
        dir = (dir + 1) % 4;
        continue;
      }
      canMove = true;
      break;
    }

    if (!canMove)
    {
      cur = nxt;
      continue;
    }

    // 3. 수확, 상태 갱신
    if (cpyBoard[nr][nc] == 3)
    {
      cpyBoard[nr][nc] = 0;
      cnt++;
    }
    cur = nxt;
    r = nr;
    c = nc;
    dir = (dir + 1) % 4;
  }

  return cnt;
}

void resetBoard()
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      cpyBoard[i][j] = board[i][j];
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

    // 무작위 위치와 무작위 방향
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        if (board[i][j])
          continue; // 산이면 PASS
        for (int dir = 0; dir < 4; dir++)
        {
          resetBoard();
          mx = max(mx, bfs({i, j, dir}));
        }
      }

    cout << "#" << t << " " << mx << "\n";
  }
}
