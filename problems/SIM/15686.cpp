#include <bits/stdc++.h>
using namespace std;

/* 전략
1. 개별 조합을 계산하기 위해 보드에는 0과 1만 표시하고, 2는 벡터에 저장한다
2. 벡터에서 M개의 좌표를 꺼내어 보드에 배치한다.
3. 해당 조합에 대하여 도시 치킨거리를 구해야한다. 이를 위해,
1) 집 하나에서 치킨 거리를 구하는 함수를 작성한다
2) (3.1)을 사용하여 모든 집의 치킨거리를 누산; 도시 치킨거리를 구한다.

4. (2),(3)을 모든 조합에 대해 반복하며, minDist 전역변수를 갱신한다.
5. 최종 minDist를 출력한다.

*/

int n,m;
int board[55][55];
int memo[15][15];

int getCombination(int n, int r) {
    if (r == 0 || n == r) return 1;
    if (memo[n][r] != 0) return memo[n][r]; 

    return memo[n][r] = getCombination(n - 1, r - 1) + getCombination(n - 1, r);
}

struct Node {
  int r,c;
};
int minDist;
int cnt2;
vector<Node> chickens;
void dfs(int cur);


int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  // 1. 보드에는 1만 표시, 2는 벡터에 저장
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
      cin >> board[i][j];
      if(board[i][j]==2) {
        board[i][j]=0;
        chickens.push_back({i,j});
        cnt2++;
      } 
    }
  
  dfs(1);
}

void dfs(int cur)
{
  if(cur==getCombination(cnt2,m)){
    return;
  }
  // cnt2 중에서 m개를 꺼내어 getTotalDist
  
  dfs(cur+1); // 5C2이면 10개를 다본다
}