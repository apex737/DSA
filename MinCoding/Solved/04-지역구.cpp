#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N, mn;
int adj[10][10];
int p[10];
int mask, visited;

void dfs(int cur, const int mask)
// 어떤 정점을 선택했든 전체를 완성할 수 있어야함
{
  // Ex. mask = 1101, N=4, cur = 0
  for (int nxt = 0; nxt < N; nxt++)
  {
    // 3. Seen
    if (!(mask & (1 << nxt)))
      continue; // on 된것만 보면 됨
    if (visited & (1 << nxt))
      continue;
    if (!adj[cur][nxt])
      continue;
    visited |= (1 << nxt);
    dfs(nxt, mask);
  }
}

bool connected(int mask)
{
  // Ex. 1101_1000 같은 마스크가들어옴
  // 1. 아무 정점이나 하나 찾기
  int st = -1;
  for (int i = 0; i < N; i++)
  {
    if (mask & (1 << i))
    {
      st = i;
      break;
    }
  }

  // 2. on된 마스크끼리 연결이 되어있는지 확인
  // 단순히 연결이 되어있으면 visited를 마킹, 아니면 건너뛰기
  visited = (1 << st);
  dfs(st, mask);
  return visited == mask;
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N;
    mn = 21e8;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        cin >> adj[i][j];
    for (int i = 0; i < N; i++)
      cin >> p[i];

    /* 전략
        1. 마을을 골라서 2개로 나눈다
        2. 각각에 대해서 연결되어있는지 확인
        3. 연결되어있으면 차이 구해서 mn 갱신 */

    int full = (1 << N) - 1;
    for (int i = 1; i < (1 << N) - 2; i++)
    {
      int mask = i;
      int other = full ^ mask;
      if (!connected(mask))
        continue;
      if (!connected(other))
        continue;
      if (mask > other)
        break;
      int a = 0, b = 0;
      // mask만 보고, on이면 a에, off면 b에 누산
      for (int i = 0; i < N; i++)
      {
        if (mask & (1 << i))
          a += p[i];
        else
          b += p[i];
      }
      mn = min(mn, abs(a - b));
    }
    cout << "#" << t << " " << mn << "\n";
  }
  return 0;
}