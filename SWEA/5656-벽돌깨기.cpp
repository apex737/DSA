#include <iostream>

using namespace std;

int N, H, W;
struct Board
{
    int b[20][20];
};

Board board;
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> W >> H;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                cin >> board.b[i][j];
    }
    return 0;
}