#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int n = 7;
const int r = 3;

vector<int> v(n, 0);  
vector<int> sel(r, 0);  // Seleted Index

// vector<int> ranking; => 벡터 쓰면 중복 케이스 처리가 안됨
set<int> ranking;   // (ordered) set => 자동 정렬

// 조합 템플릿
void nCr(int curr, int st)
{
    if (curr == r)
    {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            sum += v[sel[i]];
        ranking.emplace(sum);
        return;
    }

    for (int i = st; i < n; i++)
    {
        sel[curr] = i;
        nCr(curr + 1, i + 1);  // i+1를 i로 바꾼게 중복조합 nHr
    }
}

int T;
int main()
{
    cin >> T;

    for(int t=1; t<=T; t++)
    {
        ranking.clear();
        for(int i=0; i<n; i++) 
            cin >> v[i];
        nCr(0, 0);
        /* 벡터 오름차순 정렬 했는데 중복 때문에 틀림
            sort(ranking.begin(), ranking.end(), [](int a, int b){ 
                return a > b;    
            }); 
        */ 

        // set은 자동 오름차순 정렬이고, rbegin() 은 가장 끝에 있는 원소를 가리키는 반복자를 반환하니까,
        // 역참조 하면 최대값을 얻을 수 있음
        auto it = ranking.rbegin(); 
        std::advance(it, 4);

        cout << "#" << t << " " << *it << "\n";
    }


    return 0;
}