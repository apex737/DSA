#include <bits/stdc++.h>
using namespace std;

int n;
int ans = 0;

struct Board {
    int a[21][21];
};

int getMax(const Board& b) {
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ret = max(ret, b.a[i][j]);
        }
    }
    return ret;
}

// 한 줄을 "왼쪽으로 민다"고 생각하고 처리
vector<int> compressLine(const vector<int>& line) {
    vector<int> v;
    for (int x : line) {
        if (x != 0) v.push_back(x);
    }

    vector<int> res;
    for (int i = 0; i < (int)v.size(); i++) {
        if (i + 1 < (int)v.size() && v[i] == v[i + 1]) {
            res.push_back(v[i] * 2);
            i++; // 다음 칸은 이미 합쳐졌으므로 스킵
        } else {
            res.push_back(v[i]);
        }
    }

    while ((int)res.size() < n) res.push_back(0);
    return res;
}

Board moveBoard(const Board& b, int dir) {
    Board nxt{};
    
    if (dir == 0) { // 상
        for (int c = 0; c < n; c++) {
            vector<int> line;
            for (int r = 0; r < n; r++) {
                line.push_back(b.a[r][c]);
            }
            vector<int> res = compressLine(line);
            for (int r = 0; r < n; r++) {
                nxt.a[r][c] = res[r];
            }
        }
    }
    else if (dir == 1) { // 하
        for (int c = 0; c < n; c++) {
            vector<int> line;
            for (int r = n - 1; r >= 0; r--) {
                line.push_back(b.a[r][c]);
            }
            vector<int> res = compressLine(line);
            for (int r = n - 1, idx = 0; r >= 0; r--, idx++) {
                nxt.a[r][c] = res[idx];
            }
        }
    }
    else if (dir == 2) { // 좌
        for (int r = 0; r < n; r++) {
            vector<int> line;
            for (int c = 0; c < n; c++) {
                line.push_back(b.a[r][c]);
            }
            vector<int> res = compressLine(line);
            for (int c = 0; c < n; c++) {
                nxt.a[r][c] = res[c];
            }
        }
    }
    else { // 우
        for (int r = 0; r < n; r++) {
            vector<int> line;
            for (int c = n - 1; c >= 0; c--) {
                line.push_back(b.a[r][c]);
            }
            vector<int> res = compressLine(line);
            for (int c = n - 1, idx = 0; c >= 0; c--, idx++) {
                nxt.a[r][c] = res[idx];
            }
        }
    }

    return nxt;
}

void dfs(int depth, const Board& b) {
    ans = max(ans, getMax(b));

    if (depth == 5) return;

    for (int dir = 0; dir < 4; dir++) {
        Board nxt = moveBoard(b, dir);
        dfs(depth + 1, nxt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Board b{};
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b.a[i][j];
        }
    }

    dfs(0, b);
    cout << ans << '\n';
}