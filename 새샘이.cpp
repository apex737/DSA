#include <iostream>
#include <vector>

vector<int> v;
int sel[3];
int n, r;
void comb(int curr, int st)
{
    if (curr == r)
    {
        int sum = 0;
        for (int i = 0; i < 3; i++)
            sum += v[sel[i]];
        return;
    }

    for (int i = st; i < n; i++)
    {
        sel[curr] = i;
        comb(curr + 1, st + 1);
    }
}
using namespace std;
int main()
{
    return 0;
}