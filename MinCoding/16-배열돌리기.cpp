#include <iostream>
#include <vector>
#include <algorithm>
#define TIME_LIMIT 60 * 9

int N, M, T;
using namespace std;

int mx;
int dist[40][40];
vector<int> hotels;
vector<bool> seen;
int airport;

struct Node
{
    char c;
    int t;
    int s;
};

vector<Node> nodes;
vector<int> path, optimalPath;

// 리프까지 거리가 전부 다르다
void dfs(int curr, int day, int sum, int totalTime)
{
    // 1. 갈 수 있는 노드를 전부 선택
    // (N개의 브랜치 중에서 호텔/공항은 제외하고 여행지만 탐색)
    for (int next = 1; next <= N; next++)
    {
        if (curr == next)
            continue;
        if (nodes[next].c != 'P')
            continue;
        if (!seen[next])
        {
            int usedTime = totalTime + dist[curr][next] + nodes[next].t;
            if (usedTime <= TIME_LIMIT)
            {
                seen[next] = 1;
                path.push_back(next);
                // day는 유지한채로 여행지만 추가 탐색
                dfs(next, day, sum + nodes[next].s, usedTime);
                path.pop_back();
                seen[next] = 0;
            }
        }
    }

    // 2. 도착지 결정 (브랜치를 추가한다)
    // 2-1. 마지막 날이 아니면 호텔
    // 호텔에 도착하면 무조건 다음날로 이동한다.
    if (day < M)
    {
        for (auto hotel : hotels)
        {
            int usedTime = dist[curr][hotel] + totalTime;
            if (usedTime <= TIME_LIMIT)
            {
                path.push_back(hotel);
                dfs(hotel, day + 1, sum, 0);
                path.pop_back();
            }
        }
    }
    // 2-2. 마지막 날이면 공항
    else
    {
        int usedTime = dist[curr][airport] + totalTime;
        if (usedTime <= TIME_LIMIT)
        {
            if (mx < sum)
            {
                mx = sum;
                optimalPath = path;
                return;
            }
        }
    }
}

int main()
{
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

        // 초기화
        seen.assign(N + 1, 0);   // 방문 표식
        nodes.assign(N + 1, {}); // 노드 전체
        hotels.clear();
        mx = 0;
        path.clear();
        optimalPath.clear();

        for (int i = 1; i <= N; i++)
        {
            Node n{};
            cin >> n.c;
            if (n.c == 'P')
            {
                cin >> n.t >> n.s;
            }
            else if (n.c == 'A')
            {
                airport = i;
            }
            else if (n.c == 'H')
            {
                hotels.push_back(i);
            }

            nodes[i] = n;
        }

        dfs(airport, 1, 0, 0);

        cout << "#" << t << " " << mx << " ";
        for (auto path : optimalPath)
            cout << path << " ";
        cout << airport << "\n";
    }
    return 0;
}