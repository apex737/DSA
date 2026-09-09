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

void simulate()
{
  // 1. 하강

  for (int j = 0; j < N; j++)
  {
    // 1-1. 뭐가 있으면 떨군다
    if (!board[0][j])
      continue;
    float power = 1.0f;
    // 1-2. 아래쪽 스캔하면서 최초 1을 확인
    int d;
    int i = 0;
    // 피벗 갱신은?
    for (d = 1;; d++)
    {
      if (board[i + d][j] || d >= N /* 최초 1을 확인하거나 범위 이탈  */)
        break;
    }
    for (int i = 0; i < d; i++)
      power *= 1.9f;

    // 1-3. 블럭크기 계산
    int dd;
    for (dd = d + 1;; dd++)
    {
      if (board[i + dd][j] == 0) // 블럭이 끝나면 그 전까지
        break;
    }

    int blockSize = dd - d - 1;
    // 파워가 충분하면 시뮬레이션하고 아니면 다음 열로 넘어감
    if (power >= blockSize)
    {
    }
    else
      continue;
  }
}