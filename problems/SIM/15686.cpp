#include <bits/stdc++.h>
using namespace std;
#define BIG_INT 999999
/* 전략
1. 개별 조합을 계산하기 1, 2는 벡터에 저장한다
2. 각 조합에 대하여 도시 치킨거리를 구한다. 
3. 모든 조합에 대해 반복하며, minDist를 res에 담는다.
4. res 내에서 minVal을 출력한다.
*/
int n,m;

struct Node {
  int r,c;
};

int minDist;
vector<Node> chickens;
vector<Node> houses;
vector<int> res;
void dfs(int start, const vector<Node>& dat, vector<Node>& sel);
int getDist(const vector<Node>& sel);
int getManhattanDist(const Node& a, const Node& b);

int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  // 1. 보드에는 1만 표시, 2는 벡터에 저장
  int val;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
      cin >> val;
      if(val==1) houses.push_back({i,j});
      else if(val==2) chickens.push_back({i,j});
    }
  vector<Node> sel;
  dfs(0, chickens, sel);
  int minD = BIG_INT;
  for(int val : res) minD = min(minD, val);
  cout << minD;
}

int getManhattanDist(const Node& a, const Node& b)
{
  return abs(a.r-b.r)+abs(a.c-b.c);
}

int getDist(const vector<Node>& sel)
{
  int sum = 0;
  int chickenDist;
  for(Node house : houses)
  {
    chickenDist = BIG_INT;
    for(Node chicken : sel)
      chickenDist = min(chickenDist, getManhattanDist(house, chicken));
    sum+=chickenDist;
  }
  return sum;
}

void dfs(int start, const vector<Node>& dat, vector<Node>& sel)
{
  if(sel.size()==m) {
    res.push_back(getDist(sel));
    return;
  }

  for(int i=start; i < dat.size(); i++)
  {
    sel.push_back(dat[i]);
    dfs(i+1, dat, sel);
    sel.pop_back();
  }
}
