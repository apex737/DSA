#include <bits/stdc++.h>
using namespace std;

int n;
// 1-n 오름차순 스택 push
// 스택에서 값을 꺼내서 수열을 구성하는게 pop
int arr[100001];
vector<char> res;
int main()
{
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for(int i = 0; i < n; i++) cin >> arr[i];
  stack<int> s;
  int curMax=0;
  int temp=0;
  for(int i = 0; i < n; i++)
  {
    // 4 3 6 8 7 5 2 1 
    if(curMax < arr[i]) {
      while(curMax<arr[i])
      { 
        s.push(++curMax); // 중복삽입 방지를 위한 전위형 
        res.push_back('+');
      }
      s.pop(); res.push_back('-');
    } else if (arr[i]==s.top()) {
      s.pop(); res.push_back('-');
    } else {
      cout << "NO" << "\n";
      return 0;
    }
  }
  for(char c : res) cout << c << "\n";
}