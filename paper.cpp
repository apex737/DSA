#include <iostream>
#include <vector>

using namespace std;

/* 전략
- 색종이 width별로 5개 종이 사용가능함
- 1을 찾은 다음 5개 종이 전부 대보고, 가능한것에 대해서 분기
- 처음부터 1을 전부 벡터에 담기
- size()를 베이스로 잡게되면 벌크를 쓰는경우 커버가 안됨
- 마지막 1의 위치를 종료조건으로 잡으면 된다. */
struct Pair
{
  int r, c;
};
int papers[6];
int T;
int board[14][14];
vector<Pair> pairs;
int ans;
int main()
{
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    ans = 0;
    // 5로 초기화
    std::fill(papers, papers + 6, 5);
    for (int i = 0; i < 10; i++)
      for (int j = 0; j < 10; j++)
      {
        cin >> board[i][j];
        if (board[i][j] == 1)
          pairs.push_back({i, j});
      }

    for (auto p : pairs)
    {
      // 5개 종이 전부 대보고, 가능한것에 대해서 분기
      // 꺼내려고 했는데 이미 보드에 마킹되어있으면
      // 다음으로 넘어가야한다
      Pair tp = p;
      if (board[tp.r][tp.c] == 1)
      //
    }

    cout << "#" << t << " " << ans << "\n";
  }
  return 0;
}

/**
 * curr: 현재 좌표 (i,j) 에서 N*N 뭐를 선택했는지
 */
void dfs(int cnt, int i, int j)
{
  // 1. 전부 다 봤으면 리턴하면 되는데
  if (i == 9 && j == 9)
  {
    for (int i = 1; i <= 5; i++)
      if (papers[i] < 0)
        return;
    ans = cnt;
    return;
  }

  // 좌표 갱신
  while (!board[i][j])
  {
    j++;
    if (j > 9)
    {
      i++;
      j = 0;
    }
  }

  // 2. 2x2 ... 5x5가 되는지 전부 대본다
  for (int r = 1; r < curr; r++)
    for (int c = 1; c < curr; c++)
    {
      int nr = i + r;
      int nc = j + c;
      // 하나라도 실패했다는건 이 블럭이 안맞다는 뜻
      // 그러면 다음 1 위치로 가야한다.
      if (nr >= 10 || nc >= 10 || board[nr][nc] == 0)
        return;
    }

  // 성공했다면 바로 보드에 0 마킹 + paper + cnt 갱신 후
  // 다음 dfs로 넘어간다
  // 1. 0 보드 마킹
  for (int r = 1; r < curr; r++)
    for (int c = 1; c < curr; c++)
      board[i + r][j + c] = 0;

  // 2. paper, cnt 갱신
  if (papers[curr] > 0)
  {
    papers[curr]--;
    ans++;
  }
  else
  {
    ans = -1;
    return;
  }

  // 3. 다음으로
  dfs(curr + 1, )

  // 4. 보드 복원

  // 보드가 전부 0마킹되면 리턴?

  // 3. 된다고 하면  싹다
  // 그러면 dfs 내부에서 전체 케이스를 돌려야함
}