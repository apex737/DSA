#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;
int N, M, K;
int board[55][55];

struct Rotates
{
    int r, c, s;
};

struct Pair
{
    int r, c;
};

int getMinRow(int N, int M);
void rotate(const Pair &st, const Pair &en);
void printAll();
vector<Rotates> vr;
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M >> K;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> board[i][j];

        vr.clear();
        while (K--)
        {
            int r, c, s;
            cin >> r >> c >> s;
            vr.push_back({r, c, s});
        }

        // 회전연산
        for (auto p : vr)
        {
            auto [r, c, s] = p;
            Pair topLeft{r - s - 1, c - s - 1};
            Pair botRight{r + s - 1, c + s - 1};
            rotate(topLeft, botRight);
            // printAll();
        }
        cout << "#" << t << " " << getMinRow(N, M) << "\n";
    }

    return 0;
}

void printAll()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}

// 별다른 알고리즘없이 실제로 한칸씩 이동하는건 불가능하다.
// 벡터로 백업해놓고 한번에 덮어쓰는 방식을 써야할듯
// 우 -> 하 -> 좌 -> 상 (strict)
int dc[] = {1, 0, -1, 0};
int dr[] = {0, 1, 0, -1};
void rotate(const Pair &st, const Pair &en)
{
    /* 전략
    st+en / 2 ; 즉 중점을 기준으로 모든 좌표를 시계방향회전
    (1,2) , (5, 6) => (3, 4) */
    int n = (en.r - st.r) / 2;
    Pair mid{(en.r + st.r) / 2, (en.c + st.c) / 2};
    Pair lst = mid;
    for (int i = 1; i <= n; i++)
    {
        // 좌상단 시작점으로 이동
        // 1. 값을 벡터에 저장
        lst = Pair{lst.r - 1, lst.c - 1};
        int sz = (2 * i) * 4;
        deque<int> dq(sz);
        dq[0] = board[lst.r][lst.c];
        int rowSz = 2 * i + 1;
        for (int dir = 0; dir < 4; dir++)
        {
            int nr, nc;
            for (int d = 1; d < rowSz; d++)
            {
                nr = lst.r + dr[dir] * d;
                nc = lst.c + dc[dir] * d;
                dq[(dir * (rowSz - 1)) + d] = board[nr][nc];
            }
            // 피벗 갱신
            lst.r = nr;
            lst.c = nc;
        }

        // 2. 회전
        // deque쓰면 링크드리스트라 금방끝나는데
        // 배열의 회전은?? std::rotate?
        int back = dq.back();
        dq.pop_back();
        dq.push_front(back);

        // 3. 재배치
        board[lst.r][lst.c] = dq[0];
        for (int dir = 0; dir < 4; dir++)
        {
            int nr, nc;
            for (int d = 1; d < rowSz; d++)
            {
                nr = lst.r + dr[dir] * d;
                nc = lst.c + dc[dir] * d;
                board[nr][nc] = dq[(dir * (rowSz - 1)) + d];
            }
            // 피벗 갱신
            lst.r = nr;
            lst.c = nc;
        }
    }
}

int getMinRow(int N, int M)
{
    int row;
    int mn = 9999;
    for (int i = 0; i < N; i++)
    {
        row = 0;
        for (int j = 0; j < M; j++)
            row += board[i][j];
        mn = min(mn, row);
    }
    return mn;
}