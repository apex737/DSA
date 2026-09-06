#include <bits/stdc++.h>
using namespace std;

struct Pos
{
    int r, c;
};

int N, M;

Pos monster[4];
Pos person[4];

// 0 ~ M-1   : monster
// M ~ 2M-1  : person
Pos eventPos[8];

int memo[1 << 8][9];
int fullMask;

int dist(Pos a, Pos b)
{
    return abs(a.r - b.r) + abs(a.c - b.c);
}

Pos getPos(int cur)
{
    // 시작점
    if (cur == 2 * M)
        return {0, 0};

    return eventPos[cur];
}

// mask : 이미 처리한 이벤트
// cur  : 현재 위치
//
// return:
// 여기서부터 모든 의뢰를 끝내는 최소 추가 거리
int go(int mask, int cur)
{
    // 전부 처리 완료
    if (mask == fullMask)
        return 0;

    // 이미 이 상태 계산했음
    int& ret = memo[mask][cur];

    if (ret != -1)
        return ret;

    ret = 1e9;

    Pos now = getPos(cur);

    // --------------------------------
    // 1. 아직 안 잡은 몬스터 잡기
    // --------------------------------
    for (int i = 0; i < M; i++)
    {
        // 이미 잡았다
        if (mask & (1 << i))
            continue;

        int nxtMask = mask | (1 << i);

        ret = min(
            ret,
            dist(now, eventPos[i])
            + go(nxtMask, i)
        );
    }

    // --------------------------------
    // 2. 잡은 몬스터를 의뢰인에게 전달
    // --------------------------------
    for (int i = 0; i < M; i++)
    {
        int monsterBit = i;
        int personBit = M + i;

        // 몬스터를 아직 안 잡음
        if (!(mask & (1 << monsterBit)))
            continue;

        // 이미 전달함
        if (mask & (1 << personBit))
            continue;

        int nxtMask = mask | (1 << personBit);

        ret = min(
            ret,
            dist(now, eventPos[personBit])
            + go(nxtMask, personBit)
        );
    }

    return ret;
}

int main()
{
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;

        M = 0;

        // -----------------------------
        // 1. 입력
        // -----------------------------
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                int x;
                cin >> x;

                if (x > 0)
                {
                    monster[x - 1] = {r, c};
                    M = max(M, x);
                }
                else if (x < 0)
                {
                    person[-x - 1] = {r, c};
                    M = max(M, -x);
                }
            }
        }

        // -----------------------------
        // 2. 이벤트 좌표 배열 생성
        // -----------------------------
        for (int i = 0; i < M; i++)
        {
            eventPos[i] = monster[i];
            eventPos[M + i] = person[i];
        }

        // -----------------------------
        // 3. 모든 이벤트 완료 mask
        // -----------------------------
        fullMask = (1 << (2 * M)) - 1;

        // -----------------------------
        // 4. DP 초기화
        // -----------------------------
        memset(memo, -1, sizeof(memo));

        // -----------------------------
        // 5. 시작
        // -----------------------------
        int start = 2 * M;

        int answer = go(0, start);

        cout << "#" << tc << " " << answer << "\n";
    }
}