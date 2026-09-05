#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define DEPTH 3
// 어떤 경로로 갔는지 파악하기 위한 배열
// index selector
int path[DEPTH] = {-1};

void dfs(int curr)
{
    // 1. 일단 들어가면 무조건 실행하는 위치
    if(true /* Prune Cond */ ){

    }

    if (curr == DEPTH /* Leaf Cond */) {
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        // 2. leaf/prune에 안걸리는 경우 실행
        path[curr] = i;
        dfs(curr + 1);
        // 3. 리턴 이후 실행 
        path[curr] = -1;
    }
}
int main()
{
    dfs(0);
    return 0;
}