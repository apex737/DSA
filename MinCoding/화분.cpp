#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, p;

/* 전략: DP

DP의 3요소
1. D-table 정의:
=> D[i][A]; i번째에 A 경로로 도착할 때 최대값
=> D[i][B]; i번째에 B 경로로 도착할 때 최대값

2. 초기값 Fix
3. 점화식 작성

*/

int A[22];
int B[22];
int D[22][2];

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> p;
        for (int i = 0; i < N; i++)
            cin >> A[i];
        for (int i = 0; i < N; i++)
            cin >> B[i];

        // 1. 초기값
        D[0][0] = A[0];
        D[0][1] = B[0];

        // 2. 점화식
        for (int i = 1; i <= N; i++)
        {
            D[i][0] = max(A[i] + D[i - 1][0] - p, A[i] + D[i - 1][1]);
            D[i][1] = max(B[i] + D[i - 1][1] - p, B[i] + D[i - 1][0]);
        }

        cout << "#" << t << " " << max(D[N - 1][0], D[N - 1][1]) << "\n";
    }
    return 0;
}