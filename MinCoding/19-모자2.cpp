#include <iostream>
#include <algorithm>
using namespace std;

int N;
int people[505];
int hat[505];
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> people[i];
        for (int i = 0; i < N; i++)
            cin >> hat[i];
        sort(people, people + N);
        sort(hat, hat + N);

        // 투포인터 시작
        int p, h, sum;
        p = h = sum = 0;
        while (p < N && h < N /**/)
        {
            // people, hat
            if (people[p] + 3 < hat[h])
            {
                // 사람이 너무 작다; 사람을 올리면 된다.
                p++;
            }
            else if (people[p] > hat[h] + 3)
            {
                // 모자가 너무 작다; 모자를 올리면 된다.
                h++;
            }
            else
            { // 매칭
                p++;
                h++;
                sum++;
            }
        }
        cout << "#" << t << " " << sum << "\n";
    }

    return 0;
}