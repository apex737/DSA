/* 투포인터 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int wish[505];
int real[505];
bool seen[505];
int N, cnt;
// 최대 몇 명

/* 소트 + 그리디
2 3 4 8
5 6 7 10

에지:
8이 10을 쓰면되는데 굳이 5를 가져가서
2가 못쓰게 되는 상황
*/

int main()
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        cnt = 0;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            cin >> wish[i];
            seen[i] = 0;
        }
        for (int i = 0; i < N; i++)
            cin >> real[i];
        sort(wish, wish + N);
        sort(real, real + N);

        for (int i = 0; i < N; i++)
            for (int j = 0; j <= i; j++)
                if (!seen[i])
                {
                    if (abs(wish[i] - real[j]) <= 3)
                    {
                        seen[i] = 1;
                        cnt++;
                    }
                }
        cout << "#" << t << " " << cnt << "\n";
    }
    return 0;
}

/*
1
6
4 9 1 1 2 3
5 3 9 2 8 7

*/