#include <bits/stdc++.h>
using namespace std;


int arr[100005];

void rangePrint(int i, int j)
{
  int sum = 0;
  for(int k = i; k <= j; k++) {
    sum += arr[k];
  }
  cout << sum << "\n";
}

// 정답률보니까 시간초과날것같은디..
int main()
{
  cin.tie(0)->sync_with_stdio(0);
  int n,m;
  cin >> n >> m;
  for(int i=1;i<=n;i++) cin>>arr[i];
  while(m--)
  {
    int start, end;
    cin >> start >> end;
    rangePrint(start, end);
  }
}