#include <iostream>

using namespace std;
void dfs(int depth)
{
    // P를 하나 더 방문하는 선택들
    for (int i = 0; i < 2; i++)
    {
        cout << "P" << i << " 방문\n";
        dfs(depth + 1);
    }

    // P를 더 방문하지 않고 호텔로 가는 선택
    cout << "Hotel 도착\n";
}

int main()
{
  dfs(0);
  return 0;
}