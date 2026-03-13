#include <bits/stdc++.h>
using namespace std;

int F, S, G, U, D;
bool seen[1000001];

struct Node {
    int x, d;
};

int main() {
    cin >> F >> S >> G >> U >> D;

    queue<Node> q;
    q.push({S, 0});
    seen[S] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.x == G) {
            cout << cur.d << "\n";
            return 0;
        }

        int nx1 = cur.x + U;
        int nx2 = cur.x - D;

        if (1 <= nx1 && nx1 <= F && !seen[nx1]) {
            seen[nx1] = true;
            q.push({nx1, cur.d + 1});
        }

        if (1 <= nx2 && nx2 <= F && !seen[nx2]) {
            seen[nx2] = true;
            q.push({nx2, cur.d + 1});
        }
    }

    cout << "use the stairs\n";
    return 0;
}