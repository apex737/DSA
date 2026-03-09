#include <bits/stdc++.h>
using namespace std;

int K;
int main()
{
  stack<int> stk;
  
  cin >> K;
  while(K--)
  {
    int val; // 0에서 1,000,000 사이의 값
    // 가장 최근에 쓴 수를 지우고, 아닐 경우 해당 수를 쓴다. (stk)
    
    cin >> val;
    if(val!=0) stk.push(val);
    else stk.pop();
  }
  int sum = 0;
  // int size = stk.size();
  // while(size--)
  // {
  //   sum+=stk.top(); stk.pop();
  // }
  while(!stk.empty())
  {
    sum+=stk.top(); stk.pop();
  }
  cout << sum;
}