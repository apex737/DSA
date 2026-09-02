#include <iostream>
#include <vector>
#include <algorithm>
#define TIME_LIMIT (60 * 9)

using namespace std;

int N, M, T;

int mx;
bool possible;
int dist[40][40];
vector<int> hotels, spots;     // spots: 관광포인트 인덱스만 모아둔 리스트
vector<bool> seen;
int airport;
int minHotel[40];              // v -> 가장 가까운 호텔까지의 거리
int totalScore;

struct Node {
    char c;
    int t;
    int s;
};

vector<Node> nodes;
vector<int> path, optimalPath;

void dfs(int curr, int day, int sum, int totalTime, int remain)
{
    // [가지치기 B] 남은 만족도를 전부 먹어도 최고 기록을 못 넘으면 버린다
    if (sum + remain <= mx) return;

    // 마지막 날이면 지금 위치에서 공항으로 복귀 가능한지 확인
    if (day == M && totalTime + dist[curr][airport] <= TIME_LIMIT && sum > mx)
    {
        mx = sum;
        optimalPath = path;
    }

    for (int next : spots)
    {
        if (seen[next]) continue;

        int usedTime = totalTime + dist[curr][next] + nodes[next].t;
        if (usedTime > TIME_LIMIT) continue;

        // [가지치기 A] next까지 갔을 때 오늘의 종착지로 돌아올 시간이 남는가
        int exitTime = (day < M) ? minHotel[next] : dist[next][airport];
        if (usedTime + exitTime > TIME_LIMIT) continue;

        seen[next] = 1;
        path.push_back(next);
        dfs(next, day, sum + nodes[next].s, usedTime, remain - nodes[next].s);
        path.pop_back();
        seen[next] = 0;
    }

    if (day < M)
    {
        for (int hotel : hotels)
        {
            int usedTime = totalTime + dist[curr][hotel];
            if (usedTime > TIME_LIMIT) continue;

            path.push_back(hotel);
            dfs(hotel, day + 1, sum, 0, remain);
            path.pop_back();
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

        seen.assign(N + 1, 0);
        nodes.assign(N + 1, {});
        hotels.clear();
        spots.clear();
        path.clear();
        optimalPath.clear();
        mx = 0;
        airport = 0;
        totalScore = 0;

        for (int i = 1; i <= N; i++)
        {
            Node n{};
            cin >> n.c;
            if (n.c == 'P') {
                cin >> n.t >> n.s;
                spots.push_back(i);
                totalScore += n.s;
            }
            else if (n.c == 'A') airport = i;
            else if (n.c == 'H') hotels.push_back(i);
            nodes[i] = n;
        }

        // 모든 간선이 240분 이하이므로, 호텔이 하나라도 있으면(또는 M==1이면)
        // 관광 없이 호텔만 찍는 경로가 항상 성립한다
        possible = (M == 1) || !hotels.empty();

        for (int i = 1; i <= N; i++)
        {
            minHotel[i] = 1e9;
            for (int h : hotels)
                minHotel[i] = min(minHotel[i], dist[i][h]);
        }

        if (possible) dfs(airport, 1, 0, 0, totalScore);

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
