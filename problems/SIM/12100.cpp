#include <bits/stdc++.h>
using namespace std;

/* 노드의 이동방식과 보드의 위치가 정의되어있다..
- 전형적인 BFS 아닌가? 
- 그러면 진짜로 큐 패턴을 써야할까? 
: Yes. 그래야 모든 노드를 공평하게 이동시킬수 있으니까
- 하지만 이동에는 순서가 존재하기 때문에 그걸 컨트롤하는게 핵심인듯? */
// 방향에 맞게 루프를 돌며 한 줄씩 처리

// mov 상하좌우: 엣지로 전부이동
// 가능하면 merge -> 벽에다 짜부

// 
int n;
struct Board {
  int board[21][21];
};

Board b;
int dr[]={1,0,-1,0}; 
int dc[]={0,1,0,-1}; 

int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) 
      cin >> b.board[i][j];
  
  dfs(0, b);
  /* mov
  1) 각 행/열이 독립적으로 val!=0인 노드를 만날때까지 이동한다
  2) val!=0인 노드를 만나면 merge 하거나 stop 한다.  */ 

}

  
void dfs(int cur, Board b)
{
  
}