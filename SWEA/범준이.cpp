#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define LIMIT 540

using namespace std;
int N, M;
int dist[40][40];
struct Node
{
  char c;
  int t; // 소요시간
  int s; // 만족도
};

int mx;
bool seen[40];
set<int> hidx;
int airport;
vector<Node> v;

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
    hidx.clear();
    // 노드명, 체류시간, 만족도
    v.assign(N + 1, {});
    for (int i = 1; i <= N; i++)
    {
      Node n;
      cin >> n.c;
      // 호텔과 공항 인덱스 저장
      if (n.c == 'A')
        airport = i;
      else if (n.c == 'H')
        hidx.insert(i);
      else
        cin >> n.t >> n.s;
      // 간선거리가 노드의 순서를 따르기 때문에 필수
      v[i] = n;
    }

    dfs(airport, 0, 0, 0);
    cout << "#" << t << " " << mx << "\n";
  }
  return 0;
}

// 마지막 도착 노드를 고정한채로 거기에 도달하는 최적의 경로를 완전탐색하는 문제
// 현재 위치에서 호텔중 어느 하나쪽으로 가는 경우에 540 이내로 들어올 수 없다면 가지치기
/**
 * @param: curr:  현재 노드
 * @param: day:   며칠
 * @param: sum:   만족도 누산
 * @param: usedTime:  540분 이내 리턴 체크용
 * @attention: baseCase:
 * @attention: generalCase:
 */
void dfs(int curr, int day, int sum, int totalTime)
{
  // 다음 노드 탐색
  for (int i = 1; i <= N; i++)
  {
    // 중복 여부 체크
    if (i == airport)
    {
      if (day == M)
      {
        mx = max(mx, sum);
        return;
      }
      continue;
    }
    // 호텔에 도착한 경우 어떤 경우든지; 일단 다음 날로 넘어감
    if (hidx.find(i) != hidx.end())
    {
      // 호텔까지 간선거리 구하고 유효하다면 들어가고
      // 유효하지 않으면? 이 경로를 폐기한다.
      int usedTime = dist[curr][i] + totalTime;
      if (usedTime <= LIMIT)
      {
        dfs(i, day + 1, sum, usedTime);
      }
      else
      {
        continue;
      }
    }

    if (!seen[i])
    {
      int nextTime = totalTime + v[i].t + dist[curr][i];
      if (nextTime <= LIMIT)
      {
        seen[i] = 1;
        // day를 넘기는건 조건이 필요함
        // 호텔을 만난경우?
        dfs(i, day, sum + v[i].s, nextTime);
        seen[i] = 0;
      }
    }
  }
}