#include <iostream>
#include <vector>

using namespace std;

int ans, N;
int arr[10];
bool seen[10];
int total;

void dfs(int curr, int sumLeft, int sumRight)
{
    
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        ans = 0;
        total = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
            total += arr[i];
            seen[i] = 0;
        }
        dfs(0, 0, 0);
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}