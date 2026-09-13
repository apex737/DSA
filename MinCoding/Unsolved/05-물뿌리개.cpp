#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int trees[101];
int main()
{
  int T;
  cin >> T;
  for(int t=1; t<=T; t++)
  {
    cin >> N;
    int mx = 0;

    for(int i=0; i<N; i++) {
      cin >> trees[i];
      mx = max(mx, trees[i]);
    }

  return 0;
  }
}