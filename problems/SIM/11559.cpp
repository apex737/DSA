#include <bits/stdc++.h>
using namespace std;

struct Node {
    int r, c;
};

struct Board {
    char a[12][6];
};

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

bool bfs(Board& b) 
{
  bool seen[12][6] = {};
  bool popped = false;

  for (int i = 0; i < 12; i++) 
  {
    for (int j = 0; j < 6; j++) 
    {
      if (b.a[i][j] == '.' || seen[i][j]) continue;

      char color = b.a[i][j];
      queue<Node> q;
      vector<Node> comp;

      q.push({i, j});
      seen[i][j] = 1;
      // 백업을 할 바에 벡터를 하나 더 쓰는게 낫다
      comp.push_back({i, j});

      while (!q.empty()) 
      {
        auto cur = q.front(); q.pop();

        for (int dir = 0; dir < 4; dir++) 
        {
          int nr = cur.r + dr[dir];
          int nc = cur.c + dc[dir];

          if (nr < 0 || nr >= 12 || nc < 0 || nc >= 6) continue;
          if (seen[nr][nc]) continue;
          if (b.a[nr][nc] != color) continue;

          seen[nr][nc] = 1;
          q.push({nr, nc});
          comp.push_back({nr, nc});
        }
      }

      if ((int)comp.size() >= 4) 
      {
        popped = true;  // 바로 리턴X; 동시에 터지는 것도 1회로 간주
        for (auto &x : comp) {
          b.a[x.r][x.c] = '.';  // 터질 위치 비우기 
        }
      }
    }
  }

  return popped;
}

void popX(Board& b) {
  for (int c = 0; c < 6; c++)
  {
    vector<char> v;
    for (int r = 11; r >= 0; r--) {
      if (b.a[r][c] != '.') v.push_back(b.a[r][c]);
    }

    int idx = 11;
    for (char x : v) b.a[idx--][c] = x;
    while (idx >= 0) b.a[idx--][c] = '.';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  Board b;
  for (int i = 0; i < 12; i++)
    for (int j = 0; j < 6; j++)
      cin >> b.a[i][j];

  int chain = 0;
  while (bfs(b)) {
      popX(b);
      chain++;
  }

  cout << chain;
}