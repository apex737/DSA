#include <iostream>
#include <algorithm>
#include <vector>

/*
전략;
벡터에 넣고 소팅한다음에 N-1번째를 계속 터뜨리면서 누산하면 될거라고
그리디로 생각하면 망한다. 현재 위치가 계산에 포함되지 않기 때문에
이걸 터뜨리는게 이득일지 확신이 없기 때문이다.

DFS;;

드랍하면 자동으로 채워주는 set?.. 아이템이 복수라면 ?
그럼 멀티셋?

결론은 set이 맞다.
*/
using namespace std;

int N;
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        vector<int> v(N);
        for (int i = 0; i < N; i++)
            cin >> v[i];
        sort(v.begin(), v.end());
    }
    return 0;
}