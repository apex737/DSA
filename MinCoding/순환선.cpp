#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, ans;
vector<int> v;
int main()
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        ans = 0;
        cin >> N;
        v.resize(N);
        for (int i = 0; i < N; i++)
            cin >> v[i];

        for (int i = 0; i <= N - 3; i++)
            for (int j = i + 2; j <= N - 1; j++)
            {
                if (i == 0 && j == N - 1)
                    continue;
                int st = v[i];
                int en = v[j];
                int res;
                // 내부
                for (int a = i + 2; a <= j - 4; a++)
                    for (int b = a + 2; b <= j - 2; b++)
                    {
                        int st2 = v[a];
                        int en2 = v[b];
                        res = (st + en) * (st + en) + (st2 + en2) * (st2 + en2);
                        ans = max(ans, res);
                    }

                // 외부
                for (int a = j + 2; a <= N + i - 4; a++)
                    for (int b = a + 2; b <= N + i - 2; b++)
                    {
                        int st1 = v[a % N];
                        int en1 = v[b % N];
                        res = (st + en) * (st + en) + (st1 + en1) * (st1 + en1);
                        ans = max(ans, res);
                    }
            }
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}