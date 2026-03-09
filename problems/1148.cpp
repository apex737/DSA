#include <bits/stdc++.h>
using namespace std;

int n;
char color[1001][3];
int R[1001];
int G[1001];
int B[1001];
/* DP는 개별 case라는 가정 자체를 정의에 포함시키는
방식으로 해결; 단, 고려해야할 변수가 많을수록 테이블의 차원도 같이 증가함.
Ex. D[i][A][B]
=> i번째 도달까지 비용의 최솟값
=> 단, 1번 조건이 A이고, 2번 조건이 B인 경우에.. */

// D[k][0]: k번째까지 최소누적값, 단 i가 'R'인 경우
int D[1001][3]; 

int main()
{
  cin >> n;
  for(int i=1;i<=n;i++) 
    cin >> R[i] >> G[i] >> B[i];
  
  D[0][0] = D[0][1] = D[0][2] = 0; 
  for(int i=1;i<=n;i++)
  {
    D[i][0] = min(D[i-1][1], D[i-1][2]) + R[i];
    D[i][1] = min(D[i-1][0], D[i-1][2]) + G[i];
    D[i][2] = min(D[i-1][0], D[i-1][1]) + B[i];
  }

  cout << min({D[n][0], D[n][1], D[n][2]}) << "\n";
}