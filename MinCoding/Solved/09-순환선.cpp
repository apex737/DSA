#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
int mx;
int arr[22];
int sIdx[22];

int helper(int a, int b, int c, int d)
{
  return (arr[a] + arr[b]) * (arr[a] + arr[b]) + (arr[c] + arr[d]) * (arr[c] + arr[d]);
}

int getVal(int sIdx[])
{
  int optA = helper(sIdx[0], sIdx[1], sIdx[2], sIdx[3]);
  int optB = helper(sIdx[0], sIdx[3], sIdx[1], sIdx[2]);
  return max(optA, optB);
}

// 4개 선택
void dfs(int cur, int st)
{
  if (cur == 4)
  {
    mx = max(mx, getVal(sIdx));
    return;
  }

  for (int i = st; i < N; i++)
  {
    // 0 2 5 9 같은 경우를 방지
    if (i == N - 1 && sIdx[0] == 0)
      break;
    sIdx[cur] = i;
    dfs(cur + 1, i + 2);
  }
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N;
    mx = 0;
    for (int i = 0; i < N; i++)
      cin >> arr[i];

    dfs(0, 0);
    cout << "#" << t << " " << mx << "\n";
  }
}