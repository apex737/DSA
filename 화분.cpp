#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int ans;
int N, p;

/* 전략: DP

DP 근거
=> 최종 Optimum은 반드시 부분적으로 Optimum인 경로를 거칠 것이다.

DP의 3요소
1. D-table 정의: 현재 위치까지 올때 얻는 최대 이득
2. 초기값 Fix
3. 점화식 작성

*/

// 5 <= N <= 20
/*
INPUT

3
4 2
4 2 6 4
5 6 4 1
4 1
1 2 3 4
4 3 2 1
6 2
5 5 5 5 5 5
6 6 6 6 6 6

OUTPUT
#1 18
#2 12
#3 33

*/
int A[22];
int B[22];
int D[22];

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        ans = 0;
        cin >> N >> p;
        // 1. 초기값
        /* 여기에서 총 4가지 경우가 나온다
            A1 -> A2, A1 -> B2, B1 -> A2, B1 -> B2
        */
        //
        D[1] = max({
            A[0] + A[1] - p,
            A[0] + B[1],
            B[0] + A[1],
            B[0] + B[1] - p,
        });
        // 2. 점화식으로 D-table 채우기
        for (int i = 2; i <= N; i++)
        {
        }

        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}