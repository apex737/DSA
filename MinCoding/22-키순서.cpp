#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N, M, ans;

vector<vector<int>> fwd, bwd;
int visited[505];
int fwdCnt, bwdCnt;

void forward(int cur)
/* fwd[i] 스캔해서 cur에 의존하는 자식 정점을 탐색
    1->{5}
    3->{4}
    4->{2,6}
    5->{4,2} */
{
    // if (fwd[cur].size() == 0) return;
    for (int nxt : fwd[cur])
    {
        if (visited[nxt]) continue;
        visited[nxt] = 1;
        fwdCnt++;
        forward(nxt);
    }
}

void backward(int cur)
{
    // if (bwd[cur].size() == 0) return;
    for (int nxt : bwd[cur])
    {
        if (visited[nxt]) continue;
        visited[nxt] = 1;
        bwdCnt++;
        backward(nxt);
    }
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M;
        ans = 0;
        int u, v;
        fwd.assign(N + 1, {});
        bwd.assign(N + 1, {});


        for (int i = 0; i < M; i++)
        {
            cin >> u >> v;
            fwd[u].push_back(v);
            bwd[v].push_back(u);
        }

        /* Ex
          1->{5}
          3->{4}
          4->{2,6}
          5->{2,4}

          1. fwd에서 하나 꺼내서 visited 마킹하면서 dfs */

        for (int cur = 1; cur <= N; cur++)
        {
            fwdCnt = bwdCnt = 0;
            memset(visited, 0, sizeof(visited));
            visited[cur] = 1;
            // cnt++;
            forward(cur);
            backward(cur);
            if (fwdCnt + bwdCnt == N - 1) ans++;
        }
        cout << "#" << t << " " << ans << "\n";
    }

    return 0;
}