#include <bits/stdc++.h>
using namespace std;

/*
1. 일단 받아서 소팅부터
2. dfs에 넘겨서 depth M만큼 반복
*/
int N,M;
int arr[10001];
int printArr[10001];
void dfs(int cur)
{
  // DST
  if(cur==M){
    for(int i=0;i<M;i++) cout << printArr[i] << " ";
    cout << "\n";
    return;
  }
  // Fork & Source
  for(int i = 0; i < N; i++)
  {
    printArr[cur] = arr[i];
    dfs(cur+1);
  }
}

int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin>>N>>M;
  for(int i=0;i<N;i++)
    cin >> arr[i];
  sort(arr, arr+N);
  dfs(0);
}