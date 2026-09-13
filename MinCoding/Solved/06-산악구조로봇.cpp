#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = { 0, 0,-1, 1};

struct Edge {
    int r, c, cost;
};

struct cmp {
    bool operator()(Edge a, Edge b) {
        return a.cost > b.cost;   // 비용이 작을수록 먼저 나오는 최소 힙
    }
};

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<vector<int>> h(N, vector<int>(N));

        // ① 높이 지도 입력
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> h[i][j];

        // ② dist를 INF로 초기화, dist[0][0] = 0
        vector<vector<int>> dist(N, vector<int>(N, INT_MAX));
        dist[0][0] = 0;

        // ③ 최소 힙 준비하고 시작점 삽입
        priority_queue<Edge, vector<Edge>, cmp> pq;
        pq.push({0, 0, 0});

        // ④ 다익스트라 루프
        while (!pq.empty()) {
            // ④-a: 가장 싼 상태 꺼내기
            Edge now = pq.top();
            pq.pop();

            // ④-b: 낡은 정보면 skip
            if (now.cost > dist[now.r][now.c]) continue;

            // ④-c: 네 방향에 대해
            for (int k = 0; k < 4; k++) {
                int nr = now.r + dr[k];
                int nc = now.c + dc[k];

                // - 범위 검사
                if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

                // - 높이 차이로 이동 비용 계산 (내리막 0 / 평지 1 / 오르막 2×차이)
                int cost = /* TODO: h[now.r][now.c]와 h[nr][nc]를 비교해서 계산 */ 0;

                // - 완화(relax)
                int nextCost = now.cost + cost;
                if (nextCost < dist[nr][nc]) {
                    dist[nr][nc] = nextCost;
                    pq.push({nr, nc, nextCost});
                }
            }
        }

        cout << "#" << tc << " " << dist[N - 1][N - 1] << "\n";
    }
    return 0;
}