#include <iostream>
#include <vector>
#include <algorithm>
#define TIME_LIMIT (60 * 9)

using namespace std;

int N, M, T;

int mx;
bool possible;
int dist[40][40];
vector<int> hotels, spots;
vector<int> byCost, byScore;   // 관광포인트를 최소소요시간 오름차순 / 만족도 내림차순으로
int cost[40];                  // v를 하나 더 넣을 때 최소로 드는 총 시간
vector<bool> seen;
int airport;
int minHotel[40];
int totalScore;

struct Node {
    char c;
    int t;
    int s;
};

vector<Node> nodes;
vector<int> path, optimalPath;

// 남은 총 시간 budget으로 얻을 수 있는 만족도의 상한
int upperBound(int budget)
{
    int k = 0, acc = 0;
    for (int v : byCost)                  // 싼 것부터 몇 개나 들어갈 수 있는지
    {
        if (seen[v]) continue;
        if (acc + cost[v] > budget) break;
        acc += cost[v];
        k++;
    }
    int bound = 0;
    for (int v : byScore)                 // 그 개수만큼 비싼 점수부터
    {
        if (k == 0) break;
        if (seen[v]) continue;
        bound += nodes[v].s;
        k--;
    }
    return bound;
}

void dfs(int curr, int day, int sum, int totalTime, int remain)
{
    if (sum + remain <= mx) return;

    // [가지치기 C] 남은 시간으로 담을 수 있는 최대 만족도 기준 상계
    int budget = (M - day) * TIME_LIMIT + (TIME_LIMIT - totalTime);
    if (sum + upperBound(budget) <= mx) return;

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
        hotels.clear(); spots.clear();
        path.clear(); optimalPath.clear();
        mx = 0; airport = 0; totalScore = 0;

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

        possible = (M == 1) || !hotels.empty();

        for (int i = 1; i <= N; i++)
        {
            minHotel[i] = 1e9;
            for (int h : hotels) minHotel[i] = min(minHotel[i], dist[i][h]);
        }

        for (int v : spots)
        {
            int minIn = 1e9;
            for (int u = 1; u <= N; u++)
                if (u != v) minIn = min(minIn, dist[u][v]);
            cost[v] = nodes[v].t + minIn;
        }
        byCost = byScore = spots;
        sort(byCost.begin(), byCost.end(),
             [](int a, int b) { return cost[a] < cost[b]; });
        sort(byScore.begin(), byScore.end(),
             [](int a, int b) { return nodes[a].s > nodes[b].s; });

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
