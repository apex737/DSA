#include <iostream>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;

int N;
int board[22][22];
int visited[22][22];
struct Character
{
  int r, c, lv, exp, t;
};

struct Pos
{
  int r, c;
};

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

vector<Pos> reachable;
int res;
// 1. Reachable 후보 리스트 (BFS Flood Fill)
// 나보다 레벨 작은 몬스터 만나면 위치 벡터에 저장
bool isReachable(const Character &ch)
{
  queue<Character> q;
  q.push(ch);
  visited[ch.r][ch.c] = 1;
  while (!q.empty())
  {
    auto cur = q.front();
    q.pop();
    for (int i = 0; i < 4; i++)
    {
      int nr = cur.r + dr[i];
      int nc = cur.c + dc[i];
      if (nr < 0 || nc < 0 || nr >= N || nc >= N)
        continue;
      if (board[nr][nc] > ch.lv)
        continue;
      if (visited[nr][nc] == 1)
        continue;
      visited[nr][nc] = 1;
      if (board[nr][nc] > 0)
      {
        reachable.push_back({nr, nc});
      }
      q.push({nr, nc, ch.lv, ch.exp, ch.t + 1});
    }
  }
  if (reachable.size() == 0)
    return false;
  return true;
}

int dist(const Pos &p1, const Pos &p2)
{
  return abs(p1.r - p2.r) + abs(p2.c - p1.c);
}

// 2. 최종선택 (거리, 동점처리)
/**
 * @param r은 도달가능한 몬스터의 위치를 들고 있는 벡터
 * @return 최종 결정된 위치
 */
Pos select(const vector<Pos> &r, const Character &ch)
{
  // 사냥할 수 있는 몬스터가 1 마리일 경우는 해당 몬스터를 사냥합니다.
  if (r.size() == 1)
  {
    return r[0];
  }
  // 사냥할 수 있는 몬스터가 1 마리보다 많다면, 거리가 가까운 몬스터를 사냥합니다.
  Pos ret;
  int mn = 1e9;
  for (auto p : r)
  {
    // 1. 거리비교
    int d = dist(p, {ch.r, ch.c});
    if (mn > d)
    {
      mn = d;
      ret = {ch.r, ch.c};
    }
    // 2. 동점처리
    else if (mn == d)
    {
      // 거리가 가까운 몬스터가 여러마리이면, 가장 위에 있는 몬스터를 ,
      // 그러한 몬스터도 여러마리면, 가장 왼쪽의 몬스터를 사냥합니다.
      // Tip. else if 는 OR로 묶을 수 있다
      if (ret.r > p.r || (ret.r == p.r && ret.c > p.c))
        ret = p;
    }
  }

  return ret;
}
// 3. 상태 갱신
void update(Character &ch, const Pos &nxt)
{
  ch.t += dist(nxt, {ch.r, ch.c}); // 일단 도달 가능하면 맨하탄거리임
  ch.r = nxt.r;
  ch.c = nxt.c;
  board[ch.r][ch.c] = 0;
  if (++ch.exp == ch.lv)
  {
    ch.lv++;
    ch.exp = 0;
  }
}

int main()
{
  // 동점시 스캔순서는 배열스캔방향
  cin >> N;
  int str, stc;
  str = stc = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
      cin >> board[i][j];
      if (board[i][j] == 9)
      {
        str = i;
        stc = j;
      }
    }

  Character ch = {str, stc, 2, 0, 0};
  res = 0;

  while (isReachable(ch))
  {
    Pos nxt = select(reachable, ch);
    update(ch, nxt);
    reachable.clear();
    memset(visited, 0, sizeof(visited));
  }

  cout << ch.t << "\n";
  // bfs 결과 피드백하면서 반복
  return 0;
}