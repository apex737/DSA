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
  int r, c, d;
};

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

vector<Pos> reachable;
int res;
// 1. Reachable 후보 리스트 (BFS Flood Fill)
// 나보다 레벨 작은 몬스터 만나면 벡터에 저장
bool isReachable(const Character &ch)
{
  queue<Pos> q;
  q.push({ch.r, ch.c, 0}); // 캐릭터 위치 기준으로 거리 재계산
  visited[ch.r][ch.c] = 1;
  while (!q.empty())
  {
    auto cur = q.front();
    q.pop();
    for (int i = 0; i < 4; i++)
    {
      int nr = cur.r + dr[i];
      int nc = cur.c + dc[i];
      // B ound
      if (nr < 0 || nc < 0 || nr >= N || nc >= N)
        continue;
      // F ence: 나보다 레벨 높으면
      if (board[nr][nc] > ch.lv)
        continue;
      // S een
      if (visited[nr][nc])
        continue;
      visited[nr][nc] = 1;
      // 도달가능한, 나보다 레벨이 낮은 몬스터 위치를 벡터에 저장
      if (board[nr][nc] > 0 && board[nr][nc] < ch.lv)
      {
        reachable.push_back({nr, nc, cur.d + 1});
      }
      q.push({nr, nc, cur.d + 1});
    }
  }
  if (reachable.size() == 0)
    return false;
  return true;
}

// 2. 최종선택 (거리, 동점처리)
/**
 * @param mPos은 도달가능한 몬스터의 위치를 들고 있는 벡터
 * @return 최종 선택된 몬스터 위치
 */
Pos select(const vector<Pos> &mPos, const Character &ch)
{
  // 사냥할 수 있는 몬스터가 1 마리일 경우는 해당 몬스터를 사냥합니다.
  if (mPos.size() == 1)
  {
    return mPos[0];
  }
  // 사냥할 수 있는 몬스터가 1 마리보다 많다면, 거리가 가까운 몬스터를 사냥합니다.
  Pos ret;
  int mn = 21e8;
  for (auto p : mPos)
  {
    // 1. 거리비교
    if (mn > p.d)
    {
      mn = p.d;
      ret = p;
    }
    // 2. 동점처리
    else if (mn == p.d)
    {
      // 거리가 가까운 몬스터가 여러마리이면, 가장 위에 있는 몬스터를 ,
      // 그러한 몬스터도 여러마리면, 가장 왼쪽의 몬스터를 사냥합니다.
      if (ret.r > p.r || (ret.r == p.r && ret.c > p.c))
        ret = p;
    }
  }

  return ret;
}
// 3. 캐릭터 상태 갱신
void update(Character &ch, const Pos &nxt)
{
  ch.t += nxt.d;
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
  int sr, sc;
  sr = sc = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
      cin >> board[i][j];
      if (board[i][j] == 9)
      {
        sr = i;
        sc = j;
      }
    }

  Character ch = {sr, sc, 2, 0, 0};
  res = 0;
  board[sr][sc] = 0;

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