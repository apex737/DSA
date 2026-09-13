/*
기존 생각:
Seed 벡터를 만들어서 시뮬레이션 단계마다 상태관리를 하려고 했는데
AI 말로는 과하다고 함. 자리에 고정되어있으니까.. 근데 대안을 모르겠음
N 자체가 작으니까 매번 스캔 하는 방식도 괜찮아보인다. */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int N, M, T, mx;
int board[11][11];
int cpy[11][11];  // 시뮬레이션 과정에서 여러번 초기화 필요
int infert[11][11]; // 척박함; 여러번 심을수록 땅심이 줄어든다.

// 우-상-좌-하
/**
 * @brief 현재 dir에 따라 상대좌표가 다 틀어져서 LUT가 필요하다.
 * @example lut[0][0]: 내가 우측을 보고있을때 우측은? 아래쪽이다.
 * @example lut[0][1]: 내가 우측을 보고있을때 앞은? 우측 그대로
 * @example lut[0][2]: 내가 우측을 보고있을때 좌측은? 위쪽이다.
 * @example lut[0][3]: 내가 우측을 보고있을때 뒤는? 좌측
 */
int dir_lut[4][4] = {
    {3, 0 ,1, 2},
    {0, 1, 2, 3},
    {1, 2, 3, 0},
    {2, 3, 0, 1},
};

struct Pos
{
    int r, c, dir;
};

int simulate(Pos st);

int main()
{
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> M;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                cin >> board[i][j];
                cpy[i][j] = board[i][j];
                infert[i][j] = 4;
            }
        

        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++)
            {
                if (board[i][j])
                    continue;
                for (int dir = 0; dir < 4; dir++)
                {
                    mx = max(mx, simulate({ i, j, dir }));
                    for (int u = 0; u < N; u++)
                        for (int v = 0; v < N; v++)
                        {
                            cpy[u][v] = board[u][v];
                            infert[u][v] = 4;
                        }
                }
            }
        cout << "#" << t << " " << mx << "\n";
    }
    return 0;
}

// 우측부터 시작해서 반시계
int dc[] = { 1, 0, -1, 0 };
int dr[] = { 0, -1, 0, 1 };

bool movable(const Pos& p, int& dir)
//- 만약, 이동 가능한 곳이 여러 개인 경우,
// 로봇의 오른쪽, 앞쪽, 왼쪽, 뒤쪽의 순서로 가장 먼저인 이동 가능한 곳으로 이동한다.
{
    for (int i = 0; i < 4; i++)
    {
        int rel_dir = dir_lut[dir][i]; // 상대적 방향 계산
        int nr = p.r + dr[rel_dir];
        int nc = p.c + dc[rel_dir];
        // 빈 농지나 다 자란 농지가 없으면 계속 뺑뺑이를 돌면서 방향 검사
        if (cpy[nr][nc] == 0 || cpy[nr][nc] == (infert[nr][nc] + 3)) {
            dir = rel_dir;
            return true;
        }
    }
    return false;
}

int simulate(Pos st)
/*
- 현재 농지가 빈 농지이고 로봇이 다음 농지로 이동할 수 있는 경우 씨를 심는다.
- 현재 농지가 빈 농지이고, 로봇이 다음 농지로 이동할 수 없을 경우 아무것도 하지 않고 현재 위치에서 머무른다.
- 현재 농지에 곡식이 열린 경우 수확을 한다. 수확을 하면 농지는 빈 농지가 된다.

- 이동 가능한 곳은 빈 농지, 또는 곡식이 열린 농지이다. 산이거나 싹이 나는 농지인 경우 이동이 불가능하다.
- 만약, 이동 가능한 곳이 여러 개인 경우,
// 로봇의 오른쪽, 앞쪽, 왼쪽, 뒤쪽의 순서로 가장 먼저인 이동 가능한 곳으로 이동한다.
- 만약 이동 가능한 곳이 없는 경우 로봇은 이동하지 않고 현재 위치에 머무른다.
*/
// 1: 산; 2: 씨앗; 3: 1일차 ... 5: 3일차
{
    int r = st.r;
    int c = st.c;
    int dir = st.dir;

    int cnt = 0;
    for (int day = 1; day <= M; day++)
    {
        // 모든 씨앗의 성장
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (cpy[i][j] >= 2 && cpy[i][j] <= infert[i][j] + 2)
                    cpy[i][j]++;

        if (cpy[r][c] == 0) // 현재 농지가 빈 농지
        {
            if (movable({ r, c }, dir)) // 씨앗 심고 방향 전환
            {
                cpy[r][c] = 2; // 1: 산; 2: 씨앗; 3: 1일차 ... 5: 3일차
                r += dr[dir];    // 위치 업데이트
                c += dc[dir];
            }
            else // 현재 위치에 머무르기
            {
            }
        }

        else if (cpy[r][c] == (infert[r][c] + 3))
        {
            cnt++; // 수확
            cpy[r][c] = 0;
            infert[r][c]++; // 땅심이 감소했다
            if (movable({ r, c }, dir)) // 씨앗 심고 방향 전환
            {
                r += dr[dir]; // 위치 업데이트
                c += dc[dir];
            }
        }
    }

    return cnt;
}