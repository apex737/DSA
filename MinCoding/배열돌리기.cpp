#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
int mn = 999;

struct Operation
{
    int r, c, s;
};

struct Board
{
    int b[55][55];
};

// 배열을 넘기는 방식
Board board;
int getVal(const Board &board)
{
    int ret = 999;
    for (int i = 1; i <= N; i++)
    {
        int sum = 0;
        for (int j = 1; j <= M; j++)
        {
            sum += board.b[i][j];
        }
        ret = min(ret, sum);
    }
    return ret;
}

vector<bool> seen;
vector<Operation> Ops;

// (r,c)가 중심이고 연산횟수가 s임
// 연산을 거듭할 수록 시작점을 좌상단 모서리로 이동시킴
void rotate(Board &board, const Operation &op)
{
    int r = op.r - 1;
    int c = op.c - 1;
    for (int ss = 0; ss < op.s; ss++, r--, c--)
    {
        int width = 2 * ss + 3;
        // 1. flatten
        vector<int> tv;
        // 오른쪽
        for (int i = 0; i < width - 1; i++)
            tv.push_back(board.b[r][c + i]);
        // 아래쪽
        for (int i = 0; i < width - 1; i++)
            tv.push_back(board.b[r + i][c + width - 1]);
        // 왼쪽
        for (int i = 0; i < width - 1; i++)
            tv.push_back(board.b[r + width - 1][c + width - 1 - i]);
        // 위쪽
        for (int i = 0; i < width - 1; i++)
            tv.push_back(board.b[r + width - 1 - i][c]);

        // 2. CW rotate
        std::rotate(tv.begin(), tv.end() - 1, tv.end());

        // 3. update
        // i는 매번 초기화 j는 처음만 초기화
        int i, j;
        for (i = 0, j = 0; i < width - 1; i++, j++)
            board.b[r][c + i] = tv[j];
        // 아래쪽
        for (i = 0; i < width - 1; i++, j++)
            board.b[r + i][c + width - 1] = tv[j];
        // 왼쪽
        for (i = 0; i < width - 1; i++, j++)
            board.b[r + width - 1][c + width - 1 - i] = tv[j];
        // 위쪽
        for (i = 0; i < width - 1; i++, j++)
            board.b[r + width - 1 - i][c] = tv[j];
    }
}

void dfs(int curr, Board board)
{
    if (curr == K)
    {
        mn = min(mn, getVal(board));
        return;
    }

    for (int i = 0; i < K; i++)
    {
        if (!seen[i])
        {
            seen[i] = 1;
            Board next = board;
            rotate(next, Ops[i]);
            dfs(curr + 1, next);
            seen[i] = 0;
        }
    }
}
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {

        cin >> N >> M >> K;
        mn = 999;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                cin >> board.b[i][j];

        Ops.assign(K, {});
        for (int i = 0; i < K; i++)
        {
            cin >> Ops[i].r >> Ops[i].c >> Ops[i].s;
        }

        seen.assign(K, 0);

        dfs(0, board);
        cout << "#" << t << " " << mn << "\n";
    }
    return 0;
}
