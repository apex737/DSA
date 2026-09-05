#include <iostream>

/* 다음 입력에 대한 인접행렬/리스트 작성
7
3 1
2 3
4 1
5 2
5 4
3 5
2 4 */
using namespace std;
bool adj[8][8];
int main()
{
  int N;
  cin >> N;
  for(int i=0; i<N; i++)
    {
      int st,en;
      cin >> st >> en;
      adj[st][en]=1; // st가 en를 가리킴
    }
  return 0;
}

