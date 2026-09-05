#include <iostream>
using namespace std;

int main()
{
  // 진부분집합
  for(int tmp=0; tmp < 16; tmp++)
  {
    // 1011이면 {023} 출력 
    cout << "{";
    for(int i=0; i<4; i++)
      if(tmp & (1 << i))
        cout << i;
    cout << "}\n";
  }
  return 0;
}