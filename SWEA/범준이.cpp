#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, M;
int dist[40][40];
bool seen[40];

struct Node
{
  char c;
  int t; // 소요시간
  int s; // 만족도
};

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N >> M;
    // 간선 거리
    for (int i = 1; i <= N; i++)
      for (int j = i + 1; j <= N; j++)
      {
        cin >> dist[i][j];
        dist[j][i] = dist[i][j];
      }

    fill(seen, seen + N, 0);

    // 노드명, 체류시간, 만족도
    vector<Node> v(N + 1);
    for (int i = 1; i <= N; i++)
    {
      Node n;
      cin >> n.c;
      if (n.c == 'P')
      {
        int t, s;
        cin >> n.t >> n.s;
      }
      v[i] = n;
    }

    // 알고리즘;
    /* 마지막 날이 아닌 날에는 호텔에 체류해야함
    각 day에 대해서 모든 경로를 탐색하는 경우?
    */

    dayM(0, 0);
  }
  return 0;
}

int mx;

// 가지치기를 하지 않으면 마지막 날이 공항이 아니거나
// 마지막 종착지가 호텔이 아닌것까지 싹다 봐야한다
// 2중 DFS를 해야하고, 각각에서 가지치기가 필요하다.
void dayM(int curr, int sum)
{
  if (curr == M)
  {
    mx = max(mx, sum);
    return;
  }

  for (int i = 1; i <= N; i++)
  {
    if (!seen[i])
    {
      seen[i] = 1;
      int ss;

      if (curr == M - 1)
      {
        // 마지막날에는 공항으로 복귀
        dayM(curr + 1, sum + ss);
      }

      else
      {
        // 다른 날에는 호텔로 복귀
        dayM(curr + 1, sum + ss);
      }

      seen[i] = 0;
    }
  }
}
