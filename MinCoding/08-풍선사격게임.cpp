#include <bits/stdc++.h>
using namespace std;
int N;
int K[10];              // 풍선 값
/** 
 *@brief 중간 상태가 반복된다면 메모이제이션이다.
 *@example memo[1100_1111_00] 터지는 중간 상태라도 상관없다. 일단 이 상태로 도달하면
 메모이제이션에 의해 바로 반환 가능하기 때문에. 
*/
int memo[1 << 10];      // memo[mask] = mask 집합에서 얻는 최대 점수 (-1=미계산)

int getGain(int right, int left, int st) {
    int gain;
    bool foundR = right>=0;
    bool foundL = left>=0;
    if(foundR && foundL) gain = K[right] * K[left]; 
    else if (foundL) gain = K[left]; 
    else if (foundR) gain = K[right]; 
    else gain = K[st];
    return gain;
}

// mask: 아직 안 터진 풍선들의 집합. 그 집합의 최대 점수를 반환.
int go(int mask) {
    if(mask==0) 
        return 0;
    // TODO ②: 이미 계산된 mask면 memo 반환 (캐시)
    if(memo[mask] != -1) 
        return memo[mask];
    // TODO ③: mask에 살아있는 각 풍선 i를 "이번에 터뜨릴 것"으로 시도
    //   - i의 왼쪽/오른쪽 최근접 생존 이웃을 찾는다
    //   - 규칙대로 이번 점수 gain 계산
    //   - gain + go(i를 뺀 집합) 으로 최댓값 갱신
    int mx = 0;
    for(int i=0; i<N; i++)
    {
        if(mask & (1 << i)) {
            int right = -1, left = -1;
            // find right
            int j;
            for(j=i+1; j < N; j++) {
                if(mask & (1 << j)) {
                    right = j; break;
                }
            }
            // find left
            for(j=i-1; j >= 0; j--) {
                if(mask & (1 << j)) {
                    left = j; break;
                }
            }

            int other = mask ^ (1 << i);
            mx = max(mx, getGain(right, left, i) + go(other));
        }
    }

    // TODO ④: memo에 저장하고 반환
    return memo[mask] = mx;
}
int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        // TODO ⑤: 풍선 값 입력, memo 전부 -1로 초기화
        for(int i=0; i<N; i++) 
            cin >> K[i];
        memset(memo, -1, sizeof(memo));
        // TODO ⑥: go(전체 집합) 출력
        cout << "#" << tc << " " << go((1<<N)-1) << "\n";
    }
    return 0;
}
