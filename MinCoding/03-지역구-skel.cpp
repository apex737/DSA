#include <bits/stdc++.h>
using namespace std;

// 연결성 검사는 DFS로 한다. A에 속한 아무 마을에서 출발해, A 안의 인접 마을만 타고 DFS.
// 방문한 개수가 A의 크기와 같으면 연결된 것이다.

int N;
int adj[10][10];   // adj[i][j] = 1 이면 마을 i와 j가 인접
int p[10];         // p[i] = 마을 i의 유권자 수
int mn;
int visited;       // 방문 표시를 비트마스크로 관리 (배열 초기화 불필요)

// u에서 시작해 mask 안의 마을로만 이동하는 DFS. 방문할 때마다 visited에 표시.
/**
 * @brief : mask가 1101 이면 0->2->3번 순으로 방문
 * @param u: 시작점; u -> v 이동
 * @param mask: A/B 정보가 들어있는 마스크
 */
void dfs(int u, int mask) {
    visited |= (1 << u);    // 방문표식
    for (int v = 0; v < N; v++) {
        if (!(mask & (1 << v)))   continue;  // 다른 지역구 마을 → 못 지나감
        if (!adj[u][v])           continue;  // 길이 없음
        if (visited & (1 << v))   continue;  // 이미 방문
        dfs(v, mask);
    }
}

bool connected(int mask) {
    // TODO ①: mask가 비어 있으면 false
    if (mask == 0) return false;

    // TODO ②: mask에 속한 마을 하나를 시작점으로 잡는다
    // ex. mask = 1011_0111 에서 아무 1이나 하나만 골라 시작점으로 삼는다.
    int st = -1;
    for (int i = 0; i < N; i++) {
        if (mask & (1 << i)) { st = i; break; }
    }

    // TODO ③: 시작점에서 DFS. 단, mask에 속한 마을로만 이동한다.
    visited = 0;
    dfs(st, mask);

    // TODO ④: 방문한 마을 수 == mask의 마을 수 이면 연결됨
    return visited == mask;
}


int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        mn = 1e9;
        // TODO ⑤: 인접 행렬 N×N 읽기
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                cin >> adj[i][j];
        // TODO ⑥: 유권자 수 N개 읽기
        for(int i=0; i<N; i++) cin >> p[i];
        // TODO ⑦: mask = 1 .. (1<<N)-2 를 전부 시도
        //         ⑦-a: other = 전체 - mask
        //         ⑦-b: 둘 다 connected 인지 검사, 아니면 건너뛴다
        //         ⑦-c: 양쪽 유권자 합의 차이의 절댓값으로 최솟값 갱신

        int mask;
        // 모든 분할 경우의 수를 완전 탐색
        // 0, (1<<N)-1 은 의미없으니 Pass
        for(mask = 1; mask <= (1<<N)-2; mask++)
        {
            // ex. N=4; mask = 1101; 
            //     full = 1111; other = 0010 
            int full = ((1 << N) - 1);
            int other = full ^ mask;
            if(mask > other) break;     // 대칭구조  
            if(!connected(mask)) continue;
            if(!connected(other)) continue;
            int a, b;
            a = b = 0;
            for(int i=0; i<N; i++)
            {
                if(mask & (1 << i)) a += p[i];
                else b += p[i];
            }
            mn = min(mn, abs(a-b));
        }
        cout << "#" << t << " " << mn << "\n";
    }
    return 0;
}
