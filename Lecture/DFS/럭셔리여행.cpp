#include <iostream>
using namespace std;
int N, S, E;
int adj[11][11];
int visited[11][11];
int mx = 0, mn = 1e9;

void dfs(int cur, int sum)
{
  if (cur == E)
  {
    mx = max(mx, sum);
    mn = min(mn, sum);
    return;
  }

  //
  for (int nxt = 0; nxt < N; nxt++)
  {
    if (!adj[cur][nxt])
      continue;
    visited[cur][nxt] = 1;
    dfs(nxt, sum + adj[cur][nxt]);
    visited[cur][nxt] = 0;
  }
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      cin >> adj[i][j];
  cin >> S >> E;
  dfs(0, 0);
  cout << mx << "\n";
  cout << mn << "\n";
  return 0;
}