#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    int n, cost;
};

struct cmp
{
    bool operator()(Node a, Node b)
    {
        return a.cost > b.cost;
    }
};

vector<Node> nodes[7];

/*
1 2 1
1 3 5
2 5 1
2 4 4
3 5 1
4 6 1
5 6 2


*/
int D[8];
priority_queue<Node, vector<Node>, cmp> pq;
int main()
{

    for (int i = 1; i <= 7; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        nodes[u].push_back({v, cost});
        nodes[v].push_back({u, cost});
        D[i] = 21e8;
    }

    D[1] = 0;
    pq.push({1, 0});
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();

        // 1. lazy Deletion
        if (cur.cost > D[cur.n])
            continue;

        // 2. 갈수있는 방향 탐색
        for (Node nxt : nodes[cur.n])
        {
            // 다음 노드를 가면서 현재까지 누적비용 D에 간선비용(nxt.cost)을 치르면서 이동
            int nxtCost = nxt.cost + D[cur.n];
            // 3. relaxation
            // 더 싼 경로를 발견하면 누적비용 갱신
            if (D[nxt.n] > nxtCost)
            {
                D[nxt.n] = nxtCost;
                pq.push(nxt);
            }
        }
    }

    cout << D[6];

    return 0;
}
