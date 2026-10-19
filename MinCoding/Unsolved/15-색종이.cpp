#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 10;
int mn;
struct Pos {
	int r, c;
};
vector<Pos> seeds;
int board[11][11];
int paper[6];
bool attachable(Pos p, int width);
void attach(Pos p, int width, bool mode);
void dfs(int cur, int sum);


int main()
{
	int T;
	cin >> T;
	/*
	1. 모든 1을 벡터에 넣기
	2. 시드에 1x1 ~ 5x5 대보기
	3. mn 갱신 안되면 -1 리턴
	
	*/
	for (int t = 1; t <= T; t++)
	{
		mn = 21e8;
		for (int i = 1; i <= 5; i++)
			paper[i] = 5;
		seeds.clear();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> board[i][j];
				if (board[i][j]) {
					seeds.push_back({ i, j });
				}
			}

		if (seeds.size() == 0) {
			cout << "#" << t << " " << 0 << "\n";
			continue;
		}

		dfs(0, 0);
		// Edge: 만약에 텅빈 보드면? 
		cout << "#" << t << " " << (mn == 21e8 ? -1 : mn) << "\n";
	}

	return 0;
}


bool attachable(Pos p, int width)
{
	if (paper[width] == 0)
		return false;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
		{
			int nr = p.r + i;
			int nc = p.c + j;
			if (nr < 0 || nc < 0 || nr >= N || nc >= N) return false;
			if (!board[nr][nc]) return false;
		}
	return true;
}


void attach(Pos p, int width, bool mode)
{
	// attachable 검사를 했으니까, 일단 들어왔으면 무조건 붙일 수 있음
	if (mode)
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < width; j++)
			{
				int nr = i + p.r;
				int nc = j + p.c;
				board[nr][nc] = 0;
			}
		paper[width]--;
	}
	else
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < width; j++)
			{
				int nr = i + p.r;
				int nc = j + p.c;
				board[nr][nc] = 1;
			}
		paper[width]++;
	}
}

void dfs(int cur, int sum)
{
	if (sum >= mn) return;

	if (cur == seeds.size()) {
		mn = min(mn, sum);
		return;
	}

	// 시드위치 확인해봤는데 이미 붙어있음
	Pos s = seeds[cur];
	if (board[s.r][s.c] == 0) {
		dfs(cur + 1, sum); // 다음 시드로
		return;
	}

	// v[i]가 시드 위치
	for (int w = 5; w >= 1; w--)
	{
		if (attachable(s, w))
		{
			attach(s, w, 1);
			dfs(cur + 1, sum + 1);
			attach(s, w, 0);
		}
	}
}