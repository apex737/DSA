#include <iostream>
#include <vector>

using namespace std;
int N, M, cnt;

struct Rotate
{
    int r, c, s;
};

struct Board
{
    int b[55][55];
};

Board board;

// 연산 주어지면 거기 맞춰서 보드 변경
// 가장 왼쪽 윗 칸이 (r-s, c-s), 가장 오른쪽 아랫 칸이 (r+s, c+s)인 정사각형을
// 시계 방향으로 한 칸씩 돌린다

int getMinRow(const Board &board)
{
    int row;
    int mn = 999;
    for (int i = 0; i < N; i++)
    {
        row = 0;
        for (int j = 0; j < M; j++)
            row += board.b[i][j];
        mn = min(mn, row);
    }
    return mn;
}

int mn;
vector<bool> seen;
vector<Rotate> vRot;

// 보드를 한칸씩 CW 방향 회전
void rotate(Board &board, Rotate R)
{
    auto [r, s, c] = R;
}

void dfs(int curr, Board board)
{
    if (curr == cnt)
    {
        // 여기서는 Min값만 갱신한다.
        mn = min(mn, getMinRow(board));
        return;
    }

    for (int i = 0; i < cnt; i++)
    {
        if (!seen[i])
        {
            seen[i] = 1;
            rotate(board, vRot[i]);
            dfs(curr + 1, board);
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
        int ans = 0;
        cin >> N >> M >> cnt;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> board[i][j];
        /* 전략
        1) 회전 연산을 구현
        2) 마지막에 최솟값 추출 연산을 구현
        3) 회전을 하는 조합에 대한 순열

        */
        vRot.assign(cnt, {});
        seen.assign(cnt, 0);
        for (int i = 0; i < cnt; i++)
        {
            int r, s, c;
            cin >> r >> c >> s;
            vRot[i] = Rotate{r, c, s};
        }

        dfs(0);
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}
