#include <iostream>
#include <vector>

using namespace std;
int N;
int board[505][505];
int rotated[505][505];
int main()
{
  int T;
  cin >> T;
  for(int t=1; t<=T; t++)
  {
    cin >> N;
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
      {
        cin >> board[i][j];
        rotated[i][j]=0;
      }
    
    // 1. 하강
    // 2. 우측하강.. 을 할수도 있지만.. 떨구는 시뮬레이션 함수를
    // 잘 구현해서 기존 배열을 CW 회전시키면 편할듯
    int sum = 0;
    bool mode = false;
    simulate();
    
    for(int i=0; i<N; i++)
      sum += board[N-1][i];
    rotateBoard();
    simulate();
    for(int i=0; i<N; i++)
      sum += rotated[N-1][i];
    
    cout << "#" << t << " " << sum << "\n";

  }
  return 0;
}

void rotateBoard()
{
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
    {

    }

}

void simulate()
{
  // 1. 하강
  for(int j=0; j<N; j++)
  {
    // 1-1. 뭐가 있으면 떨군다
    if(!board[0][j]) continue;
  }
}