#include <iostream>
#include <algorithm>
using namespace std;

int ans;
int N;
int str, stc;

int board[51][51];
int visited[51][51];
int mx;
struct Pos
{
    int r, c;
};
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

void dfs(int cur, int sum, Pos piv)
{
    if (cur == 3)
    {
        ans += sum;
        return;
    }

    // 4방향 보면서 쫄 위치확인 & 그 다음부터가 다음 착수 위치
    for (int i = 0; i < 4; i++)
    {
        //
        for (int d = 1;; d++)
        {
            int nr = piv.r + dr[i] * d;
            int nc = piv.c + dc[i] * d;
            // 1. 쫄 탐색 시작
            // 어차피 테두리에 쫄 발견해봤자 못쓴다
            if (nr < 1 || nc < 1 || nr >= N - 1 || nc >= N - 1)
                continue;
            if (board[nr][nc])
            // 쫄을 발견했다
            {
                // 2. 그 쫄 다음 위치로 포의 착수위치 확인
                for (int dd = d + 1;; dd++)
                {
                    nr += piv.r + dr[i] * dd;
                    nc += piv.c + dc[i] * dd;
                    if (nr < 0 || nc < 0 || nr >= N || nc >= N)
                        goto NEXT;
                    if (visited[nr][nc])
                        continue;

                    // 3. 기존 마커 제거하고 새로운 마커 생성한 뒤, DFS
                    board[piv.r][piv.c] = 0;
                    board[nr][nc] = 2;
                    visited[nr][nc] = 1;
                    if (board[nr][nc])
                    {

                        dfs(cur + 1, sum + 1, {nr, nc});
                    }
                    else
                    {
                        dfs(cur + 1, sum, {nr, nc});
                    }
                    visited[nr][nc] = 0;
                }
            }
        NEXT:;
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
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                cin >> board[i][j];
                if (board[i][j] == 2)
                {
                    st.r = i;
                    st.c = j;
                }
            }

        dfs(0, 0, st);
        cout << "#" << t << " " << ans << "\n";
    }
    return 0;
}