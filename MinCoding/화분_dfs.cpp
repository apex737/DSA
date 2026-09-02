#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, p, mx;

int A[22];
int B[22];

void dfs(int curr, int sum, bool prev)
{
    if(curr==N) {
        mx = max(mx, sum);
        return;
    }

    if(!prev)   // 0: 이전에 A 골랐다
    {
        dfs(curr+1, sum + A[curr] - p, 0);  // A (0) -> A (0)
        dfs(curr+1, sum + B[curr], 1);      // A (0) -> B (1)
    }
    else        // 1: 이전에 B 골랐다
    {
        dfs(curr+1, sum + A[curr], 0);      // B (1) -> A (0)
        dfs(curr+1, sum + B[curr] - p, 1);  // B (1) -> B (1)
    }
}
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        mx = -1;
        cin >> N >> p;
        for (int i = 0; i < N; i++)
            cin >> A[i];
        for (int i = 0; i < N; i++)
            cin >> B[i];

        dfs(1, A[0], 0);    // 이전에 A 골랐다는 상태 정보를 넘겨줌
        dfs(1, B[0], 1);    // 이전에 B 골랐다는 상태 정보를 넘겨줌

        cout << "#" << t << " " << mx << "\n";
    }
    return 0;
}