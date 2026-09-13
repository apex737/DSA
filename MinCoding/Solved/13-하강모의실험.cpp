// #define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

struct MyBlock
{
	int st, en;
	int size;
	float power;
};
int N;
int board[505][505];
int rotated[505][505];
void simulate(int arr[][505]);
void attachBlock(int j, int arr[][505], MyBlock cur, MyBlock& nxt, bool done);
int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> board[i][j];
				rotated[i][j] = 0;
			}

		// 1. 하강
		// 2. 우측하강.. 을 할수도 있지만.. 떨구는 시뮬레이션 함수를
		// 잘 구현해서 기존 배열을 CW 회전시키면 편할듯
		int sum = 0;
		int sumRotated = 0;
		simulate(board);

		for (int i = 0; i < N; i++)
			sum += board[N - 1][i];

		// board -> rotated
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				rotated[j][N - 1 - i] = board[i][j];

		simulate(rotated);
		for (int i = 0; i < N; i++)
			sumRotated += rotated[N - 1][i];

		cout << "#" << t << " " << sum << " " << sumRotated << "\n";
	}
	return 0;
}



/* 투포인터 기반 배열탐색 시뮬레이션 */
void simulate(int arr[][505])
/* 전략
1. 다음 블럭의 시작위치를 확인
2. 다음 블럭의 사이즈를 확인
3. 현재 블럭의 하강 파워 계산
4. 다음 블럭에 현재 블럭 붙이기
  - 이전 블럭 구조체를 현재 블럭 구조체로 가져오기
5. ST 탐색위치 갱신하고 1-4 반복
*/
{
	for (int j = 0; j < N; j++)
	{
		// 뭐가 있으면 떨군다
		if (!arr[0][j] || arr[1][j])
			continue;

		int st, en;
		st = en = 0;
		MyBlock cur{ 0, 0, 1, 1.0f };
		MyBlock nxt{ 0, 0, 1, 1.0f };;
		bool done = false;
		// 전역포인터 en이 범위를 이탈할 때까지 반복
		while (en < N)
		{
			// 1. 다음 블럭의 시작위치를 확인
			// 최소 한칸 떨어져있음
			for (st = cur.en + 1;; st++)
			{
				if (arr[st][j])
					break;
				if (st >= N) {
					// 현재 블럭을 attach하고 끝내기
					done = true;
					attachBlock(j, arr, cur, nxt, done);
					goto NEXT_J;
				}
			}

			nxt.st = st;

			// 2. 다음 블럭의 시작위치와 사이즈를 확인
			for (en = st + 1; ; en++)
			{
				// en은 발견된 블럭의 다음 위치에놓인다.
				if (!arr[en][j])
					break; 
				  // 블럭이 끝까지 이어져있는 경우 
				if (en >= N) {
					// 현재 블럭을 기존 블럭에 붙이고 다음 열로 넘어간다.
					nxt.en = N - 1;
					nxt.size = nxt.en - nxt.st + 1;
					done = true;
					attachBlock(j, arr, cur, nxt, done);
					goto NEXT_J;
				}
			}

			// 3. 현재 블럭의 하강 파워 계산
			int fallDist = nxt.st - cur.en - 1;
			nxt.en = en - 1;
			nxt.size = nxt.en - nxt.st + 1;
			for (int i = 0; i < fallDist; i++)
				cur.power *= 1.9f;

			// 파워가 달리면 여기서 Attach & Break
			if (cur.power <= nxt.size) {
				attachBlock(j, arr, cur, nxt, false);	
				break;
			}

			//  4. 다음 블럭에 현재 블럭 붙이기
			// - 이전 블럭 구조체를 현재 블럭 구조체로 가져오기
			attachBlock(j, arr, cur, nxt, done);
			cur = nxt;
		}

	NEXT_J:;
	}
}

void attachBlock(int j, int arr[][505], MyBlock cur, MyBlock& nxt, bool done)
/*
다음블럭의 시작과 끝을 알고
현재블럭의 시작과 끝을 안다면
후자에 전자를 붙일 수 있다.
		 [    ][   ]
*/
{
	// 1. 기존 블럭 없애기
	for (int i = 0; i < cur.size; i++) {
		arr[i + cur.st][j] = 0;
	}

	int offset;
	if (done)
	/*	cur을 끝부분에 붙이고 마무리한다.
		이미 cur.st, cur.en을 알고있다.
		[   현재 블럭   ] [ 남은 공간 ] 
	*/
	{
		int spaceLeft = N - 1 - nxt.en;
		for (int i = 0; i < cur.size; i++) {
			offset = nxt.st + spaceLeft;
			arr[i + offset][j] = 1;
		}

		return;
	}


	// 2. 다음 블럭 위에 현재 블럭 붙이기
	// 1 1 [] [] 1 1 1 
	for (int i = 0; i < cur.size; i++) {

		// 범위이탈: arr[i + nxt.st - cur.size][j] = 1;
		offset = nxt.st - cur.size;
		arr[i + offset][j] = 1;
	}

	// 3. 다음 블럭 상태 갱신
	nxt.st = nxt.st - cur.size;
	// nxt.en은 그대로
	nxt.power = cur.power + nxt.size;
	// 여기서 nxt.size의 의미가 진짜로 attach된 다음 블럭 크기로 바뀜
	nxt.size = nxt.en - nxt.st + 1;
}