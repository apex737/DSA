#include <iostream>
#include <cstring>

using namespace std;

int N;
int board[55][55];
int eaten[55][55];
struct Pos
{
    int r, c;
};

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};
void dfs(int cur, Pos p)
{
    if (cur == 3)
        return;

    // 1. 무한루프로 쫄 찾기
    for (int i = 0; i < 4; i++)
    {
        bool found = false;
        int nr, nc, d;
        for (d = 1;; d++)
        {
            nr = p.r + dr[i] * d;
            nc = p.c + dc[i] * d;
            if (nr < 0 || nc < 0 || nr >= N || nc >= N)
                break;
            if (board[nr][nc])
            {
                found = true;
                break;
            }
        }
        if (!found)
            continue;

        // 2. 무한루프로 다음 쫄/빈칸 찾기
        for (int dd = d + 1;; dd++)
        {
            nr = p.r + dr[i] * dd;
            nc = p.c + dc[i] * dd;
            if (nr < 0 || nc < 0 || nr >= N || nc >= N)
                break;
            if (board[nr][nc])
            {
                // 두번째 쫄을 찾았다.
                eaten[nr][nc] = 1;
                board[nr][nc] = 0;
                dfs(cur + 1, {nr, nc});
                board[nr][nc] = 1;
                break;
            }

            else
            { // 빈칸이면?? 바로 들어감
                dfs(cur + 1, {nr, nc});
                // break;
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        Pos st;
        memset(eaten, 0, sizeof(eaten));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                cin >> board[i][j];
                if (board[i][j] == 2)
                {
                    st.r = i;
                    st.c = j;
                    board[i][j] = 0;
                }
            }
        dfs(0, st);
        int ans = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                ans += eaten[i][j];
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}