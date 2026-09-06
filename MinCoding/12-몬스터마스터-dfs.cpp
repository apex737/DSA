#include <bits/stdc++.h>
using namespace std;
int dist(const pair<int,int>& st, const pair<int,int>& en)
{
  return abs(st.first - en.first) + abs(st.second - en.second);
}

int board[11][11];
struct Node
{
  int n, r, c;
};
vector<Node> m;
vector<Node> p;
int N, M, mn;

// 처리한 쌍 수; 현재 위치;
int visitedM[5];
int visitedP[5];
void dfs(int cur, pair<int,int> pos, int sum)
{
  if(sum > mn) return;
  if(cur == N) {
    mn = min(mn, sum);
    return;
  }

  // 처음에는 m에게 가야함
  for(int i=0; i<m.size(); i++) {
    if(!visitedM[i])
    {
      visitedM[i]=1;
      // 여기서 다음 몬스터에게 갈수도 있지만, 다음 사람에게 갈수도 있다
      pair<int,int> nxtPos  = {m[i].r, m[i].c};
      dfs(cur, nxtPos, sum + dist(pos, nxtPos));
      visitedM[i]=0;
    }
  }

  // 처음에는 리프노드로 가기때문에 모든 몬스터를 다 훑은다음에 사람에게 간다
  for(int i=0; i<p.size(); i++) {
    // 아직 몬스터에게 가지 않았다면 사람에게 갈 수 없다.
    if(!visitedM[i]) continue;
    if(!visitedP[i])
    {
      visitedP[i] = 1;
      pair<int,int> nxtPos  = {p[i].r, p[i].c};
      dfs(cur+1, nxtPos, sum + dist(pos, nxtPos));
      // 반납하고 돌아옴
      visitedP[i] = 0;
    }
  }
}

int main()
{
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++)
  {
    cin >> N;
    mn = 1e9;
    memset(visitedM, 0, sizeof(visitedM));
    memset(visitedP, 0, sizeof(visitedP));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        cin >> board[i][j];
        if(board[i][j] > 0) {
          m.push_back({board[i][j], i, j});
        } else if (board[i][j] < 0) {
          p.push_back({board[i][j], i, j});
        }
      }
    M = m.size();
    // sort ?
    sort(m.begin(), m.end(), [](Node a, Node b){return a.n < b.n;});
    sort(p.begin(), p.end(), [](Node a, Node b){return a.n > b.n;});
    dfs(0, {0,0}, 0);
    cout << "#" << tc << " " << mn << "\n";
  }
  return 0;
}