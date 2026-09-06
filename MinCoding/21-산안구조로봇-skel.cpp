#include <bits/stdc++.h>
using namespace std;
int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};
struct Edge { int node, cost; };   // node = r*N+c 로 칸을 번호화
struct cmp { bool operator()(Edge a, Edge b){ return a.cost > b.cost; } };
int N, M;
int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M;
        vector<vector<int>> h(N, vector<int>(N));
        // TODO ①: 높이 입력
        // TODO ②: 인접리스트 구성
        //   - 각 칸의 상하좌우 간선 (비용: 내리막0/평지1/오르막2×차)
        //   - 터널 M개: A↔B 양방향, 비용 C  ← 06번과 유일한 차이
        // TODO ③: (0,0)=노드0 에서 다익스트라
        // TODO ④: dist[(N-1)*N+(N-1)] 출력
        cout << "#" << tc << " " << 0 << "\n";
    }
    return 0;
}