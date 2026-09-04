#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int board[20][20];
int mn;

vector<bool> seen;
int path[16];

void comb(int cur, int st)
{
  if (cur == N / 2)
  {
    // N/2개로 조합선택
    bool inA[16] = {};
    for (int i = 0; i < N / 2; i++)
      inA[path[i]] = 1;

    int a = 0, b = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        if (i == j)
          continue;
        if (inA[i] && inA[j])
          a += board[i][j];
        else if (!inA[i] && !inA[j])
          b += board[i][j];
      }
    mn = min(mn, abs(a - b));
    return;
  }
  for (int i = st; i < N; i++)
  {
    path[cur] = i;
    comb(cur + 1, i + 1);
  }
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    mn = 1e9;
    cin >> N;
    seen.assign(N, 0);
    memset(path, -1, sizeof(path));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        cin >> board[i][j];
    comb(0, 0);
    cout << "#" << t << " " << mn << "\n";
  }

  return 0;
}