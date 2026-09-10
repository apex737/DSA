#include <iostream>
#include <vector>

using namespace std;
int N;
int board[505][505];
int rotated[505][505];
void simulate();

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        cin >> board[i][j];
        rotated[i][j] = 0;
      }

    // 1. 하강
    // 2. 우측하강.. 을 할수도 있지만.. 떨구는 시뮬레이션 함수를
    // 잘 구현해서 기존 배열을 CW 회전시키면 편할듯
    int sum = 0;
    simulate();

    for (int i = 0; i < N; i++)
      sum += board[N - 1][i];

    // board -> rotated
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        rotated[j][N - 1 - i] = board[i][j];

    simulate();
    for (int i = 0; i < N; i++)
      sum += rotated[N - 1][i];

    cout << "#" << t << " " << sum << "\n";
  }
  return 0;
}

struct Block
{
  int st, en;
  int size;
  float power;
};

/* 투포인터 기반 배열탐색 시뮬레이션 */
void simulate()
/* 전략
1. 다음 블럭의 시작위치를 확인
2. 다음 블럭의 사이즈를 확인
3. 현재 블럭의 하강 파워 계산
4. 다음 블럭에 현재 블럭 붙이기
  - 이전 블럭 구조체를 현재 블럭 구조체로 가져오기
5. ST 탐색위치 갱신하고 1-4 반복
*/
{
  int st, en;
  Block cur{0, 0, 1, 1.0f}, nxt;
  bool nxtFlag = false;
  for (int j = 0; j < N; j++)
  {
    // 뭐가 있으면 떨군다
    if (!board[0][j])
      continue;

    // 1. 최초 1 위치를 확인
    for (st = cur.st + 1;; st++)
    {
      if (board[st][j])
        break;
      if (st >= N)
      {
        nxtFlag = true;
        break;
      }
    }
    if (nxtFlag)
      continue;

    // 2. 얼마나 붙어있는지 확인하면서 en 갱신
    for (en = st + 1;; en++)
    {
      if (!board[en][j])
      {
        nxt.en = en - 1;
        break;
      }

      if (en >= N) // 블럭이 바닥에 붙어있음
      {
        // 기존 블럭을 위에 붙이고 마무리
        // 기존 블럭의 시작/끝, 다음 블럭의 시작/끝 위치가 필요하다
        // 그래야 기존 블럭을 0으로 밀고, 다음블럭에 붙일수 있다.
        for (int i = cur.st; i < cur.size; i++)
          board[i][j] = 0;
        // nxt.st 위쪽에 반대방향으로 쭉 붙여준다
        for (int i = st - cur.size; i < cur.size; i++)
        {
          board[i][j] = 1;
        }
        nxtFlag = true;
        break; // ?
      }
    }
    if (nxtFlag)
      continue;

    nxt.size = en - st + 1;

    // 3. 파워 계산하고 블럭 사이즈와 비교
    for (int i = 0; i < st - 1; i++)
      cur.power *= 1.9f;
    // 3-1. 블럭이 더 크면 continue
    if (cur.power > nxt.size)
      continue;

    // 기존 블럭을 위에 붙이고 마무리
    for (int i = cur.st; i < cur.size; i++)
      board[i][j] = 0;
    // nxt.st 위쪽에 붙여준다
    nxt.st = st - cur.size;
    for (int i = nxt.st; i < cur.size; i++)
    {
      board[i][j] = 1;
    }
    // 다음 블럭 갱신
    nxt.power = cur.power + nxt.size;
    nxt.size = nxt.en - nxt.st + 1;
    cur = nxt;
  }
}