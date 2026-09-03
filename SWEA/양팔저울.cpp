#include <iostream>
#include <vector>

using namespace std;

int ans, N;

// 방문표식(인덱스)은 1차원인데, 선택 메모장은 2차원인 상황인듯?
//
int arr[10];
bool seen[10];

int total;

void dfs(int curr, int sumLeft, int sumRight)
{
    // 시간초과 방지용 가지치기
    // R쪽에 다 때려넣어도 왼쪽보다 딸린다
    // 끝까지 안봐도 빠른 리턴이 가능하다..!
    if (sumLeft > sumRight + (total - sumLeft))
    {
        ans++;
        return;
    }
    if (curr == N)
    {
        ans++;
        return;
    }

    for (int br = 0; br < N; br++)
    {
        // 그다음에 넣을 아이템
        int itemNext = arr[br];
        if (!seen[br])
        {
            seen[br] = 1;
            // 왼쪽에는 맘대로 넣어도됨
            dfs(curr + 1, sumLeft + itemNext, sumRight);

            // 우측에 넣을때 sumL이 sumR에 역전당하면 안된다.
            // 순서대로 접근하고 있는 문제..
            // L이 지금 당장 R보다 작으면 무조건 넘어가버린다

            // 내가 R에 이걸 넣을때, 남은 수로 커버할 수 있으면
            // R을 넣어도 좋다.
            // left right 순서 문제
            int testR = sumRight + itemNext;
            int res = total - testR;
            if (res > testR)
            {
                dfs(curr + 1, sumLeft, sumRight + itemNext);
            }
            seen[br] = 0;
        }
    }
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        ans = 0;
        total = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
            total += arr[i];
            seen[i] = 0;
        }
        dfs(0, 0, 0);
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}