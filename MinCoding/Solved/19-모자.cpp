#include <bits/stdc++.h>
using namespace std;

/* 정렬 + 그리디 + 투포인터 */
int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int N; cin >> N;
        int ans = 0;
        vector<int> people(N), hats(N);
        for(int i=0; i<N; i++) cin >> people[i];
        for(int i=0; i<N; i++) cin >> hats[i];
        // 둘 다 오름차순 정렬
        sort(people.begin(), people.end());
        sort(hats.begin(), hats.end());
        int i, j;
        /* 투포인터
        - |사람 - 모자| ≤ 3 이면 매칭, 둘 다 전진
        - 모자가 너무 작으면 모자 전진, 아니면 사람 전진 
        ex. hats:    2 4 8 10
            people:  6 7 10 15
        */
        i = j = 0;
        while(i < N && j < N)
        {
            int p = people[i]; 
            int h = hats[j]; 
            if(abs(p-h) <= 3) {
                i++; j++; ans++;
            } else if(p + 3 < h) {
                i++;
            } else if(h + 3 < p) {
                j++;
            } 
            // 여기까지 올 일이 없다; 이미 전사건 정리를 만족
            else {

            }
        }
        cout << "#" << tc << " " << ans << "\n";
    }
    return 0;
}