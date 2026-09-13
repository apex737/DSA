#include <bits/stdc++.h>
using namespace std;
int N;
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int T;
  cin >> T;

  for (int tc = 1; tc <= T; tc++)
  {
    int N;
    cin >> N;

    vector<int> h(N);
    int mx = 0;

    for (int i = 0; i < N; i++)
    {
      cin >> h[i];
      mx = max(mx, h[i]);
    }

    int one = 0;
    int two = 0;

    for (int i = 0; i < N; i++)
    {
      int diff = mx - h[i];
      // Ex. diff = 5 = 2 + 2 + 1;
      one += diff % 2;
      two += diff / 2;
    }

    int ans = 21e8;

    // conv: 2 = 1 + 1 로 분할하는 횟수
    // Ex. 5 = 2 + 2 + 1     (two=2; one=1)
    //       = 2 + 1 + 1 + 1 (conv = 1)
    for (int conv = 0; conv <= two; conv++)
    {
      int oneAug = one + 2 * conv;  // 1 -> 3
      int twoDec = two - conv;      // 2 -> 1
      /* 고정 시퀀스 1 2 1 2 1 2 ....
      oneAug > twoDec  이면 2*oneAug - 1
      twoDec >= oneAug 이면 2*twoDec
      
      */
      int day = oneAug > twoDec ? 2*oneAug - 1 : 2 * twoDec;
      ans = min(ans, day);
    }

    cout << "#" << tc << " " << ans << '\n';
  }
  return 0;
}