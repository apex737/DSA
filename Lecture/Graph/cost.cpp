#include <iostream>
#include <vector>
#include <climits>

/* 다음 입력에 대한 인접행렬/리스트 작성
4
0 15 10 27
2 0 0 1
0 5 0 8
0 0 0 0
0 3
*/
using namespace std;
#define VERTEX_NUM 4
int mn;

struct Cost {
    int n, cost;
};

vector<vector<Cost>> adj(VERTEX_NUM);
bool visited[VERTEX_NUM];
void dfs(int cur, int sum)
{
    if (cur == 3) {
        mn = min(mn, sum);
        return;
    }

    visited[cur] = true;
    for (const auto& [nxt, co] : adj[cur])
    {
        if (visited[nxt]) continue;
        dfs(nxt, sum + co);
    }
    visited[cur] = false;
}

int cost[4][4];
int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> cost[i][j];

    // cost -> adj
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (i != j && cost[i][j] != 0) {
                adj[i].push_back({ j, cost[i][j] });
            }
        }
    mn = INT_MAX;
    dfs(0, 0);
    cout << "\n";
    cout << mn << endl;
    return 0;
}

