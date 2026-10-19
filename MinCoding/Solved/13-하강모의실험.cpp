#include <iostream>
#include <vector>

using namespace std;

int board[505][505];
int rotated[505][505];
int N;

struct Block {
	int st, en, size;
	float pwr;
};
void rotate();
void simulate(int target[][505]);
int getBot(int target[][505]);

int main()
{
	int T; 
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> board[i][j];

		simulate(board);
		int sum1 = getBot(board);
		rotate();
		simulate(rotated);
		int sum2 = getBot(rotated);

		cout << "#" << t << " " << sum1 << " " << sum2 << "\n";

	}
	return 0;
}

void rotate()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			rotated[j][N - i - 1] = board[i][j];
}

int getBot(int target[][505])
{
	int sum = 0;
	for (int j = 0; j < N; j++)
		sum += target[N - 1][j];
	return sum;
}

void simulate(int target[][505])
{
	for (int j = 0; j < N; j++)
	{
		if (target[0][j] == 0 || target[1][j] == 1) continue;
		Block cur{ 0, 0 , 1, 1.0};
		Block nxt{ 0, 0, 1, 1.0};
		int i = 0;
		while (1)
		{
		// 1. 시작 블럭 선정
			while (i < N && target[i][j] != 0) {
				i++;
			}
			cur.en = i - 1;
			cur.size = cur.en - cur.st + 1;
		// 2. 타겟 블럭 선정
			while (i < N && target[i][j] != 1) {
				i++;
			}
			nxt.st = i;
			while (i < N && target[i][j] != 0) {
				i++;
			}
			nxt.en = i - 1;
			nxt.size = nxt.en - nxt.st + 1;
		// 3. 블럭 붙이기 
			int dist = nxt.st - cur.en - 1;
			// 1. 기존 블럭을 제거한다
			for (int k = cur.st; k <= cur.en; k++) {
				target[k][j] = 0;
			}

			// 2. 기존 블럭을 다음블럭 앞에다 붙인다
			nxt.st -= cur.size;
			for (int k = 0; k < cur.size; k++)
			{
				target[k + nxt.st][j] = 1;
			}

		// 4. 내려갈수 있는지 검사
			if (i == N) break;	// 종료

			bool fallable = true;
			for (int i = 0; i < dist; i++)
				cur.pwr *= 1.9f;

			if (nxt.size >= cur.pwr)
				fallable = false;

		// 5. 내려갈수 있으면 (1) 및 상태갱신; 아니면 다음 j로..
			if (!fallable)
				break;

			nxt.pwr = cur.pwr + (float)nxt.size;
			nxt.size = nxt.en - nxt.st + 1;
			cur = nxt;
		}
	}
}

