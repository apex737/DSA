#include <bits/stdc++.h>

using namespace std;
/* D[i]: 2*i 직사각형 채우는 방법의 수 */

int D[1001];
int n;
int main()
{
  cin >> n;
  D[1] = 1; D[2] = 2; D[3] = 3;
  for(int i = 4; i <= n; i++)
    D[i] =( D[i-1]+D[i-2])%10007; // int ovf
  cout << D[n];
}