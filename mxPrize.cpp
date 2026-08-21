#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
int N, T, ans;

string s;

vector<set<string>> v;

/* 전략
1. 교환 수만큼 DFS 수행
2. 한번 확인한 조합은 더이상 보지 않도록 중복제거 */

void dfs(int curr)
{
    // Prune
    /* 중복 처리 패턴 ( vector <set> )
        일단 무조건 집어넣는데, 이미 본거라면 바로 리턴하기
        set.insert.first: 삽입 대상 it
        set.insert.second: 삽입 성공/실패 */
    if (!v[curr].insert(s).second)
        return;

    // D EPTH: 교환 횟수
    if (curr == N)
    {
        ans = max(ans, stoi(s));
        return;
    }

    // F ork: 가능한 모든 조합
    for (int i = 0; i < s.size() - 1; i++)
        for (int j = i + 1; j < s.size(); j++)
        {
            swap(s[i], s[j]);
            dfs(curr + 1);
            swap(s[i], s[j]);
        }
}

int main()
{
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        ans = 0;
        s.clear();
        cin >> s >> N;
        /* vector < set > 을 전부 빈 set {} 로 초기화
           추후 랜덤 액세스할 때 세그폴트 안뜨려면 N+1로 잡아서
           v[N]까지 액세스 가능하도록 함

        */
        v.assign(N + 1, {});
        dfs(0);
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}
