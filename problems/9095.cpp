#include <bits/stdc++.h>
using namespace std;
/* DP : Devide & Pile-up
 1. 목표는 D 테이블 채우기
 2. 방법은 점화식과 초기값 */ 
int D[11]; 
int main()
{
  int n;
  int a;
  D[1]=1; D[2]=2; D[3]=4;
  cin >> n;
  for(int i = 4; i <= 11; i++)
    D[i] = D[i-1]+D[i-2]+D[i-3];

  while(n--)
  {
    cin >> a;
    cout << D[a] << "\n";
  }
}