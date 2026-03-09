#include <bits/stdc++.h>
using namespace std;
/* DP : Devide & Pile-up
 1. 목표는 D 테이블 채우기
 2. 방법은 점화식과 초기값
 -> 중간단계를 누적하는 패턴에 특화되어있는 알고리즘
 */ 
 
int arr[305];
int D[305];
int main()
{
  int n;
  cin >> n;
  /* DEF: D[i]는 i까지 도착하기 위한 누적 최댓값*/
  for(int i = 1; i <= n; i++) cin >> arr[i];
  D[1] = arr[1]; 
  D[2] = arr[1]+arr[2];
  D[3] = max(arr[1], arr[2])+arr[3];
  // D[4] = max(arr[1]+arr[3], D[2])+arr[4];
  // D[5] = max(arr[2]+arr[4], D[3])+arr[4];
  for(int i = 4; i <= n; i++){
    D[i] = max(arr[i-3]+arr[i-1], D[i-2])+arr[i];
  }

  cout << D[n];
}