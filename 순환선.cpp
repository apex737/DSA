#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
int N, T, ans;
int arr[22];
struct Pair
{
    int a, b;
};

void calcMax(int st, int en)
// 1. 교차 금지: 출발 노드가 둘다 크거나 둘다 작거나
// 2. 인접 금지
// 3. 인접 출발/도착 금지
// 4. 복수 직통 금지
{
    // 1. 내부 순회
    // 인접 금지
    int a = st + 2;
    int b = en - 2;
    if (b - a >= 2)
    {
        for (int i = a; i < en - 1 - 2; i++)
            for (int j = b; j < en - 1; j++)
    }

    // 2. 외부 순회
}

int main()
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        ans = 0;
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> arr[i];

        // 1. 순회를 하려면 기준이 있어야할것같음
        // st보다 큰 인덱스를 en으로 해야 전부 탐색가능
        for (int i = 0; i < N; i++)
            for (int j = i + 2; j < N; j++)
            // 인접한거 터치하면 안되니까 +2부터 시작하고 N-2에서 끝냄
            {
                // 예외처리
                if (i == 0 && j == N - 1)
                    break;
                calcMax(i, j); // 두번째 브랜치는 여기서 따로 선택하면서 업데이트
            }

        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}