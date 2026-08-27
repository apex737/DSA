#include <iostream>
#include <vector>
#include <algorithm>

#define LIMIT 60 * 9 // 하루 9시간 제한
using namespace std;
int N, M;

/* 독해
1. 모든 지점은 3개로 분류됨; 호텔H, 관광지P, 공항A(출발지이자 도착지)
2. 하루에 9시간 넘게 관광+이동해선 안됨
3. 같은 호텔에 여러번 머물수 있다
4. 관광지에는 체류시간과 만족도가 있다

테스트 케이스

1번 줄은 2번 ~ N번 노드까지 간선거리가 표시됨
2번 줄은 3번 ~ N번 노드까지 간선거리가 표시됨...

Goal: 최대한 만족도가 높은 여행 계획
*/
struct Node
{
  char c; // A, H, P
  int t;  // 체류시간
  int s;  // 체류보상
};

int dist[40][40];

/* 2중 DFS
    outer DFS는 (m-dayCounter) M depth를 단순히 파고든다
    inner DFS는 갈 수 있는 모든 경로를 조합처럼 탐색하고
    호텔에 도착하면 dayM을 갱신한다. 마지막 날에 도달하면 최종 리턴.
*/

int mx;
vector<bool> seen;
void dayM(int m, int s, int travelTime)
{
  // 1. 가지치기
  if (travelTime > LIMIT)
    return;

  if (M == m)
  {
    mx = max(mx, s);
    return;
  }

  for (int i = 0; i <)
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    int ans;
    cin >> N >> M;
    // 파이썬 히트맵 느낌?
    for (int i = 1; i < N; i++)
      for (int j = i + 1; j <= N; j++)
      {
        int d;
        cin >> d;
        // 반대도 마찬가지
        dist[i][j] = d;
        dist[j][i] = d;
      }

    vector<Node> v(N + 1);
    vector<bool> seen(N + 1);
    for (int i = 1; i <= N; i++)
    {
      char c;
      cin >> c;
      if (c == 'P')
      {
        int s, t;
        cin >> t >> s;
        v[i] = {c, t, s};
      }
      else
      {
        v[i] = {c, 0, 0};
      }
    }

    /*  그리디?는 아님. 단방향성이 아니라 루프를 돌아서
      DP?는 개별 경로를 상태로 압축할 수 있어야하는데 고려할게 너무많다
      완탐?
      가지치기 (제약)
        마지막 날에는 반드시 마지막 노드가 A 여야한다
        그 외의 날에는 마지막 노드가 H 여야한다
        LIMIT을 넘어가면 가지치기를 한다
    */

    cout << "#" << t << " " << ans << "\n";
  }
  return 0;
}
