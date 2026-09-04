#include <iostream>
#include <queue>

using namespace std;
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
int height[33][33];
bool seen[33][33];
int memo[33][33]; // (i,j)에 도착하기 위해 필요한 최소한의 연료
int N;

struct Node
{
    int r, c;
};
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cin >> height[i][j];

        queue<Node> q;
        q.push({1, 1});
        seen[1][1] = 1;
        // 그리디 bfs로 풀리는 문제일까?
        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int nr = cur.r + dr[i];
                int nc = cur.c + dc[i];
                if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                    continue;
                if (seen[nr][nc])
                    continue;
                // memo & step 갱신
                seen[nr][nc] = 1;
                int fuelCost;
                if (height[nr][nc] > height[cur.r][cur.c])
                {
                    fuelCost += 2 * (height[nr][nc] - height[cur.r][cur.c]);
                }
                else if (height[nr][nc] == height[nr][nc])
                {
                    fuelCost += 1;
                }
            }
        }

        cout << "#" << t << " " << memo[N - 1][N - 1] << "\n";
    }
    return 0;
}