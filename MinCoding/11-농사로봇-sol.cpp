#include <iostream>
#include <algorithm>
using namespace std;
int N, M, T, mx;
int board[11][11]; // 0=농지, 1=산 (원본 지형)

// ── 작업용 상태 (매 simulate마다 초기화) ──
int state[11][11];   // 0=빈농지, 1=성장중, 2=곡식(수확가능)
int ripeDay[11][11]; // 성장중인 칸이 '곡식'이 되는 일차
int kcnt[11][11];    // 그 칸에 지금까지 심은 횟수 K (핵심!)

int dir_lut[4][4] = {
    // 열 순서 = 우선순위[오른쪽,앞,왼,뒤]
    {3, 0, 1, 2},
    {0, 1, 2, 3},
    {1, 2, 3, 0},
    {2, 3, 0, 1},
};
int dc[] = {1, 0, -1, 0};
int dr[] = {0, -1, 0, 1};

struct Pos
{
    int r, c, dir;
};

// 우선순위대로 이동 가능한(빈농지/곡식, 산 제외) 첫 방향을 찾고 dir 설정
bool movable(const Pos &p, int &dir)
{
    for (int i = 0; i < 4; i++)
    {
        int nd = dir_lut[dir][i];
        int nr = p.r + dr[nd], nc = p.c + dc[nd];
        if (board[nr][nc] == 1)
            continue; // 산이면 불가
        if (state[nr][nc] == 0 || state[nr][nc] == 2)
        { // 빈농지 or 곡식
            dir = nd;
            return true;
        }
    }
    return false;
}

int simulate(Pos s)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            state[i][j] = 0;
            ripeDay[i][j] = 0;
            kcnt[i][j] = 0;
        }

    int r = s.r, c = s.c, dir = s.dir, cnt = 0;
    for (int day = 1; day <= M; day++)
    {
        // 성장: 오늘 여무는 성장중 칸 → 곡식
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (state[i][j] == 1 && ripeDay[i][j] <= day)
                    state[i][j] = 2;

        // 오전: 수확 / 파종
        if (state[r][c] == 2)
        { // 곡식 → 수확
            cnt++;
            state[r][c] = 0;
        }
        else if (state[r][c] == 0)
        { // 빈농지
            int td = dir;
            if (movable({r, c, dir}, td))
            { // 이동 가능하면 씨 심기
                int K = ++kcnt[r][c];
                state[r][c] = 1;
                ripeDay[r][c] = day + 4 + K; // 심고1일=싹, 싹후 3+K일 → day+4+K
            }
        }
        // 오후: 이동
        if (movable({r, c, dir}, dir))
        {
            r += dr[dir];
            c += dc[dir];
        }
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M;
        mx = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> board[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == 1)
                    continue; // 산에서 시작 불가
                for (int dir = 0; dir < 4; dir++)
                    mx = max(mx, simulate({i, j, dir}));
            }
        cout << "#" << t << " " << mx << "\n";
    }
    return 0;
}
