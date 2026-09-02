#include <iostream>
#include <vector>
#include <algorithm>
#define TIME_LIMIT (60 * 9)

using namespace std;

int N, M, T;

int mx;
bool possible;                 // 조건을 만족하는 경로가 하나라도 있는가
int dist[40][40];
vector<int> hotels;
vector<bool> seen;
int airport;

struct Node {
    char c;
    int t;
    int s;
};

vector<Node> nodes;
vector<int> path, optimalPath;

void dfs(int curr, int day, int sum, int totalTime)
{
    // 1. 오늘 안에 더 돌 수 있는 관광포인트
    for (int next = 1; next <= N; next++)
    {
        if (curr == next) continue;
        if (nodes[next].c != 'P') continue;
        if (seen[next]) continue;

        int usedTime = totalTime + dist[curr][next] + nodes[next].t;
        if (usedTime > TIME_LIMIT) continue;

        seen[next] = 1;
        path.push_back(next);
        dfs(next, day, sum + nodes[next].s, usedTime);
        path.pop_back();
        seen[next] = 0;
    }

    // 2. 오늘의 종착지
    if (day < M)
    {
        for (int hotel : hotels)
        {
            int usedTime = totalTime + dist[curr][hotel];
            if (usedTime > TIME_LIMIT) continue;

            path.push_back(hotel);
            dfs(hotel, day + 1, sum, 0);
            path.pop_back();
        }
    }
    else
    {
        int usedTime = totalTime + dist[curr][airport];
        if (usedTime <= TIME_LIMIT)
        {
            possible = true;
            if (mx < sum)
            {
                mx = sum;
                optimalPath = path;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
            {
                cin >> dist[i][j];
                dist[j][i] = dist[i][j];
            }

        // === 테스트케이스 초기화 ===
        seen.assign(N + 1, 0);
        nodes.assign(N + 1, {});
        hotels.clear();
        path.clear();
        optimalPath.clear();
        mx = 0;
        possible = false;
        airport = 0;
        // =========================

        for (int i = 1; i <= N; i++)
        {
            Node n{};
            cin >> n.c;
            if (n.c == 'P')       cin >> n.t >> n.s;
            else if (n.c == 'A')  airport = i;
            else if (n.c == 'H')  hotels.push_back(i);
            nodes[i] = n;
        }

        dfs(airport, 1, 0, 0);

        cout << "#" << t << " " << mx;
        if (possible)
        {
            for (int p : optimalPath) cout << " " << p;
            cout << " " << airport;
        }
        cout << "\n";
    }
    return 0;
}
