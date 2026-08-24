#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define INF LLONG_MAX // from climits
using namespace std;
int board[55][55];

/* 전략
1. 같은 행에 있는 모든 연속된 1 이상의 수를 노드로 정의
2. 2가 포함된 노드가 출발행, 3이 포함된 노드가 도착행
3. 2의 상하에서 막힌 노드를 INF로 정의
=> 모든 노드는 행 번호를 저장하고, 막혀있음 여부를 판단하기 위해, 노드의 좌측과 우측을 저장한다

4. 다익스트라 알고리즘을 수행
1) 최단거리 배열 D를 도입하고, 2가 포함된 노드에서 출발
2) 노드 벡터를 순회하면서 도달가능 여부를 파악한다. 도달 가능하다면 INF에서 최단거리로 업데이트
3) 포지션 (head) 업데이트하고 반복
*/

struct Node
{
    int row, left, right, mark;
};

int main()
{
    int N, M;
    int ans = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> board[i][j];

    vector<Node> v;

    // 1. 맵을 스캔해서 다익스트라 노드로 매핑한다
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            if (board[i][j])
            {
                // 일단 넣고 right는 나중에 알아낼거임
                v.push_back({i, j, 0, 0});

                // 출발지 또는 도착지 노드인지 확인한다
                if (board[i][j] == 2)
                    v.back().mark = 2;
                else if (board[i][j] == 3)
                    v.back().mark = 3;

                // right를 알아낸다.
                int tj = j;
                while (tj < M && board[i][tj])
                {
                    // 출발지 또는 도착지 노드인지 확인한다
                    if (board[i][j] == 2)
                        v.back().mark = 2;
                    else if (board[i][j] == 3)
                        v.back().mark = 3;
                    tj++; // 0만나면 멈춤
                }
                j = tj;
            }
        }

    // 2. 다익스트라 알고리즘을 돌린다

    // 1) 출발행을 찾고, D 배열을 초기화한다.
    Node st;
    int dSize = v.size();
    vector<int> D(dSize);
    fill(D.begin(), D.end(), -INF);
    D[0] = 0;

    for (auto n : v)
        if (n.mark == 2)
            st = n;

    // 2) 매 루프마다 st를 업데이트하면서 한칸씩 이동하면서 도달가능한 모든 노드에 이르는
    //    최단거리를 D에 기록한다
    while (dSize--)
    {
        int minDist = 999;
        for (auto n : v)
        {

            if (n.left >= st.left && n.right <= st.right)
            {
            }
        }

        // 마지막에 st를 업데이트해서 한칸 전진
    }

    cout << ans << "\n";
    return 0;
}
