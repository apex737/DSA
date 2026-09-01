#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int arr[3] = {0};
    // 1. 타입이 벡터인 배열이므로, v.size() 연산이 안먹는다.
    vector<int> v[3] = {
        {1, 2, 3, 4, 5, 6},
        {3, 6, 5},
        {1, 1, 1, 2, 3, 4, 5}};

    v[0].push_back(7);
    v[1].push_back(7);
    v[2].push_back(7);
    for (int i = 0; i < sizeof(v) / sizeof(vector<int>); i++)
    {
        for (auto z : v[i])
            cout << z << " ";
        cout << "\n";
    }

    cout << "\n\n";

    // 2. 이차원 벡터의 크기가 가변적일때
    vector<vector<int>> v2 = {
        {1, 2, 3},
        {5, 6},
        {3, 2},
        {2, 6, 7},
        {3, 7}};

    for (int i = 0; i < v2.size(); i++)
    {
        for (auto z : v2[i])
            cout << z << " ";
        cout << "\n";
    }

    return 0;
}
