#include <bits/stdc++.h>
using namespace std;
int memo[101][101];

int getCombination(int n, int r) {
    if (r == 0 || n == r) return 1;
    if (memo[n][r] != 0) return memo[n][r]; // 이미 계산된 값 반환

    return memo[n][r] = getCombination(n - 1, r - 1) + getCombination(n - 1, r);
}

int main()
{
  cout << getCombination(25, 10) << "\n";
}