#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct Character {
	int r, c;
	int lv = 2;
	int exp = 0;

};

int dr[] = { 1,0,-1,0 };
int dc[] = { 0, 1,0,-1 };

int board[21][21];

int N;
struct Pos {
	int r, c, d;
};

vector<Pos> reachables;
bool isReachable(const Character& ch)
{
	// BFS 도달가능한, 나보다 레벨 작은 몬스터 리스트업
	reachables.clear();

	Pos st{ ch.r,ch.c,0 };
	int visited[21][21];
	memset(visited, 0, sizeof(visited));
	queue<Pos> q;
	visited[st.r][st.c] = 1;
	q.push(st);
	while (!q.empty())
	{
		Pos cur = q.front(); q.pop();

		// 까봤더니, 나보다 레벨 작은 몬스터라면
		int b = board[cur.r][cur.c];
		if (b > 0 && b < ch.lv) {
			reachables.push_back({ cur.r,cur.c,cur.d });
		}

		for (int i = 0; i < 4; i++)
		{
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
			if (visited[nr][nc]) continue;
			// Fence: 나보다 레벨 높은 몬스터 만나면 
			if (board[nr][nc] > ch.lv) continue;
			visited[nr][nc] = 1;
			q.push({ nr,nc,cur.d + 1 });

		}
	}

	// 사이즈가 0이면 아무것도 못찾았으니 종료
	return reachables.size();
}

Pos selectPos()

/*
사냥할 수 있는 몬스터가 1 마리일 경우는 해당 몬스터를 사냥합니다.
사냥할 수 있는 몬스터가 1 마리보다 많다면, 거리가 가까운 몬스터를 사냥
거리가 가까운 몬스터가 여러마리이면, 가장 위에 있는 몬스터를 ,
그러한 몬스터도 여러마리면, 가장 왼쪽의 몬스터를 사냥
=> 벡터에 몬스터의 위치를 저장
 더 이상 사냥할 수 있는 몬스터가 없으면 매크로를 중지

*/
{
	Pos nxtPos;
	if (reachables.size() == 1) {
		return reachables[0];
	}

	// sort를 잘쓰면 우선순위가 자동 처리됨
	sort(reachables.begin(), reachables.end(), [](Pos a, Pos b) {
		// 1. d가 다르면 작은걸 우선한다.
		if (a.d != b.d) return a.d < b.d;
		// 2. r이 다르면 작은걸 우선한다.
		else if (a.r != b.r) return a.r < b.r;
		// 3. c가 다르면 작은걸 우선한다.
		else
			return a.c < b.c;
	});

	return reachables[0];
}


void updateState(const Pos& nxtPos, Character& ch, int& t)
{
	// 다음위치로 이동하면서 캐릭터의 상태를 갱신하고 맵도 갱신한다.
	ch.r = nxtPos.r;
	ch.c = nxtPos.c;
	t += nxtPos.d;
	board[ch.r][ch.c] = 0;
	// exp가 레벨과 같아지면 레벨 업
	if (++ch.exp == ch.lv) {
		ch.lv++;
		ch.exp = 0;
	}
}

int main(void)
{
	/*
	1. BFS로 도달가능한, 나보다 레벨 작은 몬스터 리스트업 + 선택
	2. 해당 위치로 이동
	3. 캐릭터 상태 갱신
	*/
	cin >> N;
	Character ch;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == 9) {
				ch.r = i; ch.c = j;
				board[i][j] = 0;
			}
		}

	int elaps_time = 0;
	while (isReachable(ch))
	{
		updateState(selectPos(), ch, elaps_time);
	}

	cout << elaps_time;

	return 0;
}