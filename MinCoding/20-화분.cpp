#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, p;

/* 전략: DP

DP의 3요소
1. D-table 정의:
=> D[i][0]; i번째에 A를 선택할 때 최대 누적값
=> D[i][1]; i번째에 B를 선택할 때 최대 누적값

2. 초기값 (정의를 만족하는)
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

        // 1. (정의를 만족하는) 초기값 
        D[0][0] = A[0]; 
        D[0][1] = B[0]; 

        // 2. 점화식
        for (int i = 1; i <= N; i++)
        {
            // i번째에 A에 도착하는 최대 누적값은
            // i-1번째까지의 최대 누적값에 A[i]를 더한 것이다.
            D[i][0] = max(D[i - 1][0] - p, D[i - 1][1]) + A[i];
            D[i][1] = max(D[i - 1][1] - p, D[i - 1][0]) + B[i];
        }

        cout << "#" << t << " " << max(D[N - 1][0], D[N - 1][1]) << "\n";
    }
    return 0;
}