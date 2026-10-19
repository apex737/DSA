#include <iostream>
#include <vector>

using namespace std;

// 우하좌상
int dc[] = { 1,0,-1,0 };
int dr[] = { 0,1,0,-1 };


/*	01-사과
	2D 에서 지향 방향이 있을때 	상대적인 사분면의 위치를 정의하는 방법에 관한 문제 
	현재 지향방향이 정확히 uy (y+ 방향) 일때 몇번 우회전할지만 고려하면 된다.

	방법: 
	1) 단위벡터 uy (dir), ux ( (dir+1) % 4 ) 를 정의한다
	2) 방향벡터 v와 { uy 을 내적한 부호, ux을 내적한 부호 } 로 케이스 분류
	-> 이게 우리가 직관적으로 이해하고 있는 4분면의 수식적 정의이다.
	{+, +}: 1 turn
	{+, -}: 3 turns
	{-, +}: 3 turns
	{-, -}: 2 turns

	3) 경계에 해당하는 축에 대한 고려를 포함
	y+: 0 turn
	y-: 2 turns
	x+: 1 turn
	x-: 3 turns

	4) 결론: (2), (3)을 종합하여 Turns 케이스 분류 
	3: 좌반면 & x-축
	2: 4사분면 & y-축
	1: 1사분면 & x+축
	0: y+ 축

*/
int N; // map size
int M; // 사과의 번호; M = 3이라면, 1 2 3 이 모두 주어짐이 보장된다
int board[11][11];
int T;
struct Pos {
	int r, c;
};

int turnCnt(Pos& cur, const Pos& nxt, int& dir);
// M번 사과 좌표는 apples[M] 에 있다
vector<Pos> apples; // M <=10
int main()
{
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int turns = 0;
		cin >> N;
		M = 0;
		// 사과를 발견할 때마다 좌표와 번호를 벡터에 넣는다
		apples.assign(11, {});
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> board[i][j];
				int num = board[i][j];
				if (num > 0) {
					apples[num] = { i,j };
					M++;
				}
			}

		Pos cur = { 0,0 }; 
		int dir = 0;
		// 마지막 사과에 도착할 떄까지 반복
		for (int m = 1; m <= M; m++)
		{
			// 함수 내부에서 cur, dir를 지속 갱신
			turns += turnCnt(cur, apples[m], dir);
		}

		cout << "#" << t << " " << turns << "\n";
	}
	return 0;
}

int turnCnt(Pos& cur, const Pos& nxt, int& dir)
{
	int turns = 0;
	// 1. cur -> nxt 사분면 판단
	// 단위벡터는 2가지 성분으로 정의된다
	Pos ux, uy, v;
	uy.r = dr[dir]; uy.c = dc[dir];
	ux.r = dr[(dir + 1) % 4]; ux.c = dc[(dir + 1) % 4];
	v.c = nxt.c - cur.c;
	v.r = nxt.r - cur.r;
	int front = v.r * uy.r + v.c * uy.c;
	int right = v.r * ux.r + v.c * ux.c;

	// 2. turns수 판단
	if (right < 0) turns = 3;
	else if (front < 0) turns = 2;
	else if (right > 0) turns = 1;
	else turns = 0;

	cur = nxt;
	// turn 수 자체가 다음 방향을 알려준다
	dir = ( dir + turns) % 4;
	return turns;
}
