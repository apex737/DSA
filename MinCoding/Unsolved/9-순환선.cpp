#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
int arr[22];

int helper(int a, int b, int c, int d)
{
    return (arr[a] + arr[b]) * (arr[a] + arr[b]) + (arr[c] + arr[d]) * (arr[c] + arr[d]);
}

int getVal(int sIdx[])
{
    int optionA = helper(sIdx[0], sIdx[1],
        sIdx[2], sIdx[3]);
    int optionB = helper(sIdx[0], sIdx[3],
        sIdx[1], sIdx[2]);
    return optionA > optionB ? optionA : optionB;
}

int mx;

int sIdx[4]; // depth가 곧 사이즈
void nC4(int cur, int st)
{
    if (cur == 4) {
        // 조합에 대해서 2가지 경우에 대해서 최댓값 갱신
        mx = max(mx, getVal(sIdx));
        return;
    }

    for (int i = st; i < N; i++)
    {
        sIdx[cur] = i; // cur번째 depth에서 i를 선택했다.
        // 0 2 5 "9" 같은걸 고르면 안된다. 0-9는 인접하니까..
        // 즉 (9 + 2) % 10 = 1 > 0 이니까 안된다.
        if (sIdx[cur] + 2 > N && (sIdx[cur] + 2) % N > sIdx[0]) return;
        nC4(cur + 1, i + 2); // 조합인데, 2이상을 골라야함..
    }
}
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        mx = 0;
        memset(sIdx, -1, sizeof(sIdx));
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> arr[i];

        // 4개를 잘 선택하면 그 안에서는 2가지 케이스만 발생한다.
        /* 서로 거리가 2 스텝이상 떨어질것 */
        // 선택만 하면되고 순서는 상관 없으므로 NC4 템플릿을 사용한다.
        nC4(0, 0);
        cout << "#" << t << " " << mx << "\n";
    }
    return 0;
}
