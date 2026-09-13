#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 터진거 표시하기 위한 비트마스크 (N<=20이면 사용 가능)
int N;
int arr[11];
int poped[11];
int sel[11]={-1}; // depth k에서 뭘 선택했나?
int mx;
void dfs(int cur, int score);
int main()
{
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  
  for(int t=1;t<=T;t++)
  {
    mx = 0;
    cin >> N;
    for(int i=0; i<N; i++)
      cin >> arr[i];
    memset(poped, 0, sizeof(poped));
    // 순서가 있는 조합 (순열)
    dfs(0, 0);
    cout << "#" << t << " " << mx << "\n";
  }


  return 0;
}

void dfs(int cur, int score)
{
  if(cur == N) {
    mx = max(mx, score);
    return;
  }

  for(int i=0; i<N; i++)
  {
    if(!poped[i])
    {
      int nxtScore, target;
      // 1. 왼쪽, 오른쪽에서 안터진 최초의 풍선을 탐색
      bool leftNone = false;
      bool rightNone = false;
      int left, right;
      for(int j = i+1;;j++)
      {
        if(j>=N) {
          rightNone = true; // 오른쪽 다 터짐
          break;
        } 
        if(poped[j]) continue;
        right = j;
        break;
      }

      for(int j = i-1;;j--)
      {
        if(j<0) {
          leftNone = true; // 왼쪽 다 터짐
          break;
        } 
        if(poped[j]) continue;
        left = j;
        break;
      }

      // 2. 스코어 갱신
      nxtScore = score;
      if(leftNone && rightNone) {
        nxtScore += arr[i];
        // 여기서 리턴해버려도 되긴 할듯?
      } else if (!leftNone && !rightNone) {
        nxtScore += arr[left]*arr[right];
      } else if (!rightNone) {
        nxtScore += arr[right];
      } else {
        nxtScore += arr[left];
      }

      // 3. DFS 정규형
      poped[i]=1;
      dfs(cur+1, nxtScore);
      poped[i]=0;
    }
  }
}