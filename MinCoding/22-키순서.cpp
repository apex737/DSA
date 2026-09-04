#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/*
자신의 키를 알수 있는 정점
내 이하 정점을 전부 흡수하면서,
내 이상 정점을 전부 가리키면 된다

흡수한다=> indegree?
개별 노드는 각자만의 포인팅 벡터를 가짐
*/
map<int, vector<int>> pointing;
map<int, set<int>> pointed;
/*
두 벡터를 합했을때 전체가 되면 성공


*/

int N, M, ans;
int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N >> M;
    ans = 0;
    int st, en;
    for (int i = 0; i < M; i++)
    {
      cin >> st >> en;
      // 포인팅
      pointing[st].push_back(en);
      pointed[en].insert(st);
    }

    // 흡수관계 정리해서 pointed의 의미를 확장
    // 4를 5가 가리키는데, 그 5를 1이 가리키니까,
    // 4는 {1, 5}가 가리킨다.
    // 즉, 기존 4.pointed = {3, 5} 에서, 5.pointed의 {1}을 결합
    for (int i = 0; i < N; i++)
    {
      for (auto si : pointed[i])
      {
        // 1. 3, 5의 의존성을 확인한다
        auto innerSet = pointed[si];
        // 2. pointed[i]에 합친다
        pointed[i].insert(innerSet.begin(), innerSet.end());
      }
    }
    for (int i = 0; i < N; i++)
    {
      if (pointing.size() + pointed.size() == N)
        ans++;
    }

    cout << "#" << t << " " << ans << "\n";
  }

  return 0;
}