#include <bits/stdc++.h>
using namespace std;

int mx, start, dst, up, down;
bool seen[1000001];
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
    if(1<= nx1 && nx1<=mx && seen[nx1]==0){
      q.push({nx1,cur.d+1});
      seen[nx1]=1;
    } 
    if(1<= nx2 && nx2<=mx && seen[nx2]==0) {
      q.push({nx2,cur.d+1});
      seen[nx2]=1;
    }
  }
  cout << "use the stairs" << "\n";
  return 0;
}