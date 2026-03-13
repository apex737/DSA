#include <bits/stdc++.h>
using namespace std;

int mx, start, dst, up, down;
bool seen[101];
struct Node {
  int x,d;
};
int main()
{
  cin >> mx >> start >> dst >> up >> down;
  queue<Node> q;
  q.push({start,0});
  seen[start]=1;
  while(!q.empty())
  {
    Node cur = q.front(); q.pop();
    if(cur.x==dst){
      cout << cur.d << "\n";
      return 0;
    }
    int nx1 = cur.x+up;
    int nx2 = cur.x-down;
    // seen을 안쓰면 케이스가 너무 많이 생기고
    // 쓰게되면 이전 케이스가 seen을 선점해서 경로를 막는 문제가 생긴다.
    if(nx1<mx && seen[nx1]==0){
      q.push({nx1,cur.d+1});
      seen[cur.x]=1;
    } 
    if(nx2>=0 && seen[nx2]==0) 
      q.push({nx2,cur.d+1});
      seen[cur.x]=1;
  }
  cout << "use the stairs" << "\n";
  return 0;
}