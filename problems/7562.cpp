#include <bits/stdc++.h>
using namespace std;

/* 백트래킹(트리 재귀) : N과M(1)
1. 선형재귀
1) 루프 순회마다 재귀 플래그 확인
2) 재귀 플래그가 내려간 경우
- 리프에 도달할 때까지 재귀 플래그를 올리면서 배열 푸시
- 리프에 도달시 값 찍고 리턴하고 재귀 플래그를 내림  
- 플래그가 내려갔기 때문에 i = 4에서 한번 더 재귀

*/
int n,m;
int arr[10];
bool isused[10];

void func(int k){ // 현재 k개까지 수를 택했음.
  if(k == m){ // m개를 모두 택했으면
    for(int i = 0; i < m; i++)
      cout << arr[i] << ' '; // arr에 기록해둔 수를 출력
    cout << '\n';
    return;
  }

  for(int i = 1; i <= n; i++){ // 1부터 n까지의 수에 대해
    if(!isused[i]){ // 아직 i가 사용되지 않았으면
      arr[k] = i; // k번째 수를 i로 정함
      isused[i] = 1; // i를 사용되었다고 표시
      func(k+1); // 다음 수를 정하러 한 단계 더 들어감
      isused[i] = 0; // k번째 수를 i로 정한 모든 경우에 대해 다 확인했으니 i를 이제 사용되지않았다고 명시함.
    }
  }
}

int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  func(0);
}