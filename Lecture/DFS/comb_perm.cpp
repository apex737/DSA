#include <iostream>
#include <vector>

using namespace std;
vector<int> path;
vector<bool> seen;
int cnt = 0;
void nCr(int cur, int st)
{
    if (cur == 3)
    {
        for (int i = 0; i < 3; i++)
            cout << path[i] << " ";
        cout << "\n";
        cnt++;
        return;
    }

    for (int i = st; i <= 6; i++)
    {
        path[cur] = i;
        nCr(cur + 1, i + 1);
    }
}

void nHr(int cur, int st)
{
    if (cur == 3)
    {
        for (int i = 0; i < 3; i++)
            cout << path[i] << " ";
        cout << "\n";
        cnt++;
        return;
    }

    for (int i = st; i <= 6; i++)
    {
        path[cur] = i;
        nHr(cur + 1, i); // nCr에 비해 여기만 i+1 => i로 수정
    }
}

void nPr(int cur)
{
    if (cur == 3)
    {
        for (int i = 0; i < 3; i++)
            cout << path[i] << " ";
        cout << "\n";
        cnt++;
        return;
    }

    for (int i = 1; i <= 6; i++)
    {
        if (!seen[i])
        {
            seen[i] = 1;
            path[cur] = i;
            nPr(cur + 1);
            seen[i] = 0;
        }
    }
}

void n_Pi_r(int cur)
{
    if (cur == 3)
    {
        for (int i = 0; i < 3; i++)
            cout << path[i] << " ";
        cout << "\n";
        cnt++;
        return;
    }

    for (int i = 1; i <= 6; i++)
    {
        path[cur] = i;
        n_Pi_r(cur + 1);
    }
}

int main()
{
    cout << "============= Print nCr Start ==============\n";
    path.assign(3, -1);
    seen.assign(6, 0);
    cnt = 0;
    nCr(0, 1);
    cout << "Total: " << cnt << "\n";
    cout << "============= Print nCr END ==============\n";
    cout << "\n\n";
    cout << "============= Print nPr Start ==============\n";
    cnt = 0;
    path.assign(3, -1);
    seen.assign(6, 0);
    nPr(0);
    cout << "Total: " << cnt << "\n";
    cout << "============= Print nPr END ==============\n";
    cout << "\n\n";
    cout << "============= Print nHr Start ==============\n";
    cnt = 0;
    path.assign(3, -1);
    seen.assign(6, 0);
    nHr(0, 1);
    cout << "Total: " << cnt << "\n";
    cout << "============= Print nHr END ==============\n";
    cout << "\n\n";
    cout << "============= Print n_Pi_r Start ==============\n";
    cnt = 0;
    path.assign(3, -1);
    n_Pi_r(0);
    cout << "Total: " << cnt << "\n";
    cout << "============= Print n_Pi_r END ==============\n";
    return 0;
}