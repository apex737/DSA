#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
int arr[11];
int poped[11];
int mx;
void dfs(int cur, int score)
{
  if (cur == N)
  {
    mx = max(mx, score);
    return;
  }

  for (int i = 0; i < N; i++)
  {
    if (poped[i]) continue;
    int nxtScore;
    int left = i - 1;  // 좌측에서 처음 만나는 풍선 위치
    int right = i + 1; // 우측에서 처음 만나는 풍선 위치

    while (left >= 0 && poped[left]) left--; // 왼쪽에 풍선 탐색
    while (right < N && poped[right]) right++; // 우측 풍선탐색

    bool isLeft = left == -1;  // 왼쪽에 풍선이 없다 -> 내가 최좌측
    bool isRight = right == N; // 우측에 풍선이 없다 -> 내가 최우측
    
    if (isLeft && isRight) nxtScore = arr[i]; // 1. 나밖에 풍선이 없다 -> 나만 터지면 끝
    else if (isLeft) nxtScore = arr[right]; // 2. 내가 최좌측
    else if (isRight) nxtScore = arr[left]; // 3. 내가 최우측
    else nxtScore = arr[left] * arr[right]; // 4. 나머지 -> 좌우가 다있음

    nxtScore += score;
    poped[i] = 1;
    dfs(cur + 1, nxtScore);
    poped[i] = 0;
  }
}
int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    cin >> N;
    mx = 0;
    for (int i = 0; i < N; i++)
    {
      cin >> arr[i];
      poped[i] = 0;
    }

    // 10! 의 모든 경우를 전부 테스트해서 최고점 찾기
    dfs(0, 0);
    cout << "#" << t << " " << mx << "\n";
  }
}