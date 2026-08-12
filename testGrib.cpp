#include <iostream>
#include <vector>

using namespace std;
struct Pair
{
    int r, c;
};
int board[3][3];
// 우, 하, 좌, 상
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int main()
{
    Pair lst{0, 0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = j + 1 + 3 * i;

    vector<int> t(8);

    t[0] = board[lst.r][lst.c];
    int rowSz = 3;
    for (int dir = 0; dir < 4; dir++)
    {
        int nr, nc;
        for (int d = 1; d < rowSz; d++)
        {
            nr = lst.r + dr[dir] * d;
            nc = lst.c + dc[dir] * d;
            t[(dir * (rowSz - 1)) + d] = board[nr][nc];
        }
        // 피벗 갱신
        lst.r = nr;
        lst.c = nc;
    }

    return 0;
}