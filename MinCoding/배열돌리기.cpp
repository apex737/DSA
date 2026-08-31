#include <iostream>
#include <vector>
#include <deque>

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
// 우 -> 하 -> 좌 -> 상
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

void dequeCW(deque<int> &dq)
{
    int back = dq.back();
    dq.pop_back();
    dq.push_front(back);
}

void dequeCCW(deque<int> &dq)
{
    int front = dq.front();
    dq.pop_front();
    dq.push_back(front);
}

void rotate(Board &board, Rotate R, void (*fp)(deque<int> &dq))
{
    // 3, 4, 2 라면 center(3,4)이고 패딩이 2임
    auto [r, s, c] = R;
    int tr = r - c, tc = s - c;
    // 바깥에서 안쪽으로 이동
    while (c--)
    {
        // 1. 단방향 전진 기반 회전 템플릿
        // 배열의 값을 deque에 넣는다
        // 포인터 하나를 두고 재활용하는것도 좋을듯?
        deque<int> dq;

        dq.push_back(board.b[tr][tc]);
        for (int dir = 0; dir < 4; dir++)
        {
            int d = 2 * (c + 1) + 1; // 가로길이
            int nr, nc;
            for (int dd = 1; dd < d; dd++)
            {
                nr = tr + dr[dir] * dd;
                nc = tc + dc[dir] * dd;
                dq.push_back(board.b[nr][nc]);
            }
            dq.pop_back();
            tr = nr; // 모서리에 도달하면 피벗을 바꿈
            tc = nc;
        }

        // 2. deque의 CW => 여기만 CCW로 바꾸면 됨
        // 보드를 넘기지 않으려면 복구 로직도 fp로 재활용
        fp(dq);

        // 3. deque에서 배열로 덮어쓴다.
        while (!dq.empty())
        {
            board.b[tr][tc] = dq.front();
            dq.pop_front();
            for (int dir = 0; dir < 4; dir++)
            {
                int d = 2 * (c + 1) + 1; // 가로길이
                int nr, nc;
                for (int dd = 1; dd < d; dd++)
                {
                    // 마지막 원소 건너 뜀
                    nr = tr + dr[dir] * dd;
                    nc = tc + dc[dir] * dd;
                    if (dir == 3 && dd == d - 1)
                        break;
                    board.b[nr][nc] = dq.front();
                    dq.pop_front();
                }
                tr = nr;
                tc = nc;
            }
        }
        // tr, tc는 다시 시작점으로 돌아왔다 => 피벗을 갱신
        tr++;
        tc++;
    }
}

// 보드를 매번 직접 복사함; Depth <= 6 이라서 가능
void dfs(int curr, Board board)
{
    if (curr == cnt)
    {
        // 여기서는 Min값만 갱신한다.
        mn = min(mn, getMinRow(board));
        // dbgPrint();
        return;
    }

    for (int i = 0; i < cnt; i++)
    {
        if (!seen[i])
        {
            seen[i] = 1;
            rotate(board, vRot[i], dequeCW);
            dfs(curr + 1, board);
            seen[i] = 0;
        }
    }
}

void dbgPrint()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << board.b[i][j] << " ";
        cout << "\n";
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

        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                cin >> board.b[i][j];

        vRot.assign(cnt, {});
        seen.assign(cnt, 0);
        for (int i = 0; i < cnt; i++)
        {
            int r, s, c;
            cin >> r >> c >> s;
            vRot[i] = Rotate{r, c, s};
        }

        dfs(0, board);
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}
