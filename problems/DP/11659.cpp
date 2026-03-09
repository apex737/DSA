#include <bits/stdc++.h>
using namespace std;

int arr[100005];
// 누적합 테이블
int D[100005]; // 10^8 = 1억 < 21억; in bound
int main()
{
  cin.tie(0)->sync_with_stdio(0);
  int n,m;
  cin >> n >> m;
  
  for(int i=1;i<=n;i++) {
    cin>>arr[i];
    D[i] = D[i-1]+arr[i];
  }

  int start, end;
  while(m--)
  {
    cin >> start >> end;
    cout << D[end]-D[start-1] << "\n";
  }
}