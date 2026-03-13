#include <bits/stdc++.h>
using namespace std;

int n,m;
int arr[10];
int printArr[10];

void dfs(int cur, int idx)
{
  if(cur==m){
    for(int i=0;i<m;i++) cout << printArr[i] << " ";
    cout << "\n";
    return;
  }

  for(int i=idx; i<n;i++)
  {
    printArr[cur]=arr[i];
    dfs(cur+1, i);
  }


}

int main()
{
  cin >> n >> m;
  for(int i=0;i<n;i++)
    cin >> arr[i];      

  sort(arr,arr+n);
  dfs(0,0);
}