#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int board[55][55];

/* 전략
1. 같은 행에 있는 모든 연속된 1 이상의 수를 노드로 정의
2. 2가 포함된 노드가 출발행, 3이 포함된 노드가 도착행
3. 두 노드의 [left, right]가 겹치면 수직이동 가능
4. 다익스트라 알고리즘을 수행
1) D[i]는 st => i 까지 가는 데 필요한 최소 거리
2) nextDist = max(D[curr], 이번 수직이동 거리)
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
    int st = -1, en = -1;

    // 1. 연속적인 1이상의 수를 다익스트라 노드로 정의
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            if (board[i][j])
            {
                // 일단 넣고 (left = j); right는 나중에 알아낼거임
                int nodeIdx = v.size();
                v.push_back({i, j, 0, 0});

                int tj = j;
                while (tj < M && board[i][tj])
                {
                    // 출발, 도착 노드인지 확인
                    if (board[i][tj] == 2)
                    {
                        v.back().mark = 2;
                        st = nodeIdx;
                    }
                    else if (board[i][tj] == 3)
                    {
                        v.back().mark = 3;
                        en = nodeIdx;
                    }
                    tj++;
                }
                v.back().right = tj - 1;
                j = tj - 1;
            }
        }

    // 2. 다익스트라 알고리즘을 돌린다

    // D[i] = st에서 i번 노드까지 가는 데 필요한 최소 LIMIT
    int dSize = v.size();
    /*  D[i] == -1;               아직 가는 방법도 모름
        D[i] != -1 && !isMin[i];  가는 방법은 찾았지만 최단거리인지 모름
                                  거리 구한게, 최단거리인건 아님
        isMin[i] == 1;            경로가 최단거리임
    */
    vector<int> D(dSize, -1);
    vector<bool> isMin(dSize, 0);
    D[st] = 0;

    // 여기에서 다음 타겟노드 갱신
    // 아직 확정되지 않은 '도달 가능한' 노드 중 D가 가장 작은 노드를 고른다.
    for (int i = 0; i < dSize; i++)
    {
        int curr = -1;
        for (int j = 0; j < dSize; j++)
        {
            // 선택 노드가 없으면 일단 첫번째를 curr로 지정
            // minIdx 탐색
            if (!isMin[j] && D[j] != -1 && (curr == -1 || D[j] < D[curr]))
                curr = j;
        }

        if (curr == -1)
            break;

        isMin[curr] = 1;

        // 보석 발판이 curr로 선택됐다 == D[en]이 최소 LIMIT로 확정됐다
        if (curr == en)
            break;

        for (int next = 0; next < dSize; next++)
        {
            // 내 왼쪽이나 오른쪽에 안겹치게 있으면 점프 못함
            bool overlap = v[curr].left <= v[next].right && v[next].left <= v[curr].right;
            // 최단거리 모르는 것들 중에서 도달 가능한 노드 탐색
            if (!isMin[next] && overlap)
            {
                int d = abs(v[curr].row - v[next].row);

                // 일반적인 다익이면 여기에서 거리 누산
                // 지금까지 최대 게이지 2만 쓰고 왔는데, 다음껀 게이지 3이 든다면 nextDist = 3;
                int nextDist = max(D[curr], d);
                // 최단 거리 갱신
                if (D[next] == -1 || nextDist < D[next])
                    D[next] = nextDist;
            }
        }
    }

    cout << D[en] << "\n";
    return 0;
}