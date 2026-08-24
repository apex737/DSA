#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;
int board[55][55];

/* 전략
1. 같은 행에 있는 모든 연속된 1 이상의 수를 노드로 정의
2. 2가 포함된 노드가 출발행, 3이 포함된 노드가 도착행
3. 두 노드의 [left, right]가 겹치면 수직이동 가능
=> 간선 비용은 두 노드의 행 차이

4. 다익스트라 알고리즘을 수행
1) D[i]는 i번 노드까지 가는 데 필요한 최소 LIMIT
2) nextDist = max(D[cur], 이번 수직이동 거리)로 완화
*/

struct Node
{
    int row, left, right, mark;
};

int main()
{
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> board[i][j];

    vector<Node> v;
    int start = -1, target = -1;

    // 1. 맵을 스캔해서 다익스트라 노드로 매핑한다
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            if (board[i][j])
            {
                // 일단 넣고 right는 나중에 알아낼거임
                int nodeIdx = static_cast<int>(v.size());
                v.push_back({i, j, 0, 0});

                // right를 알아낸다.
                int tj = j;
                while (tj < M && board[i][tj])
                {
                    // 출발지 또는 도착지 노드인지 확인한다
                    if (board[i][tj] == 2)
                    {
                        v.back().mark = 2;
                        start = nodeIdx;
                    }
                    else if (board[i][tj] == 3)
                    {
                        v.back().mark = 3;
                        target = nodeIdx;
                    }
                    tj++; // 0만나면 멈춤
                }
                v.back().right = tj - 1;
                j = tj - 1;
            }
        }

    // 2. 다익스트라 알고리즘을 돌린다

    // 1) D[i] = i번 노드까지 가는 데 필요한 최소 LIMIT
    //    -1은 아직 도달하지 못한 노드를 의미한다.
    int dSize = static_cast<int>(v.size());
    vector<int> D(dSize, -1);
    vector<bool> visited(dSize, false);
    D[start] = 0;

    // 2) 아직 확정되지 않은 도달 노드 중 D가 가장 작은 노드를 고른다.
    for (int cnt = 0; cnt < dSize; cnt++)
    {
        int cur = -1;
        for (int i = 0; i < dSize; i++)
        {
            if (!visited[i] && D[i] != -1 &&
                (cur == -1 || D[i] < D[cur]))
                cur = i;
        }

        // 더 이상 도달한 노드가 없다.
        if (cur == -1)
            break;

        visited[cur] = true;

        // target이 선택된 순간 D[target]은 최종값이다.
        if (cur == target)
            break;

        for (int next = 0; next < dSize; next++)
        {
            if (visited[next])
                continue;

            // 두 구간에 공통으로 포함된 열이 있어야 수직이동할 수 있다.
            bool overlap = v[cur].left <= v[next].right &&
                           v[next].left <= v[cur].right;
            if (!overlap)
                continue;

            int verticalDist = abs(v[cur].row - v[next].row);

            // 경로의 비용은 수직이동 거리의 '합'이 아니라 '최댓값'이다.
            int nextDist = max(D[cur], verticalDist);
            if (D[next] == -1 || nextDist < D[next])
            {
                D[next] = nextDist;
            }
        }
    }

    cout << D[target] << "\n";
    return 0;
}
