#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 20000 + 10;
struct Node
{
	int dis, fuel;
	bool operator <(const Node it) const
	{
		return fuel < it.fuel;
	}
};
int N, L, P;
Node G[MAXN];
priority_queue<Node> Q;

bool cmp(Node a, Node b)
{
	return a.dis < b.dis;
}

void solve()
{
	int ans = 0, i = 0, j = P;
	while (G[i].dis < 0)
		i++;
	while (!Q.empty())
		Q.pop();

	while (i < N && j < L)
	{
		while (i < N && G[i].dis <= j)
		{
			Q.push(G[i]);
			i++;
		}
		if (Q.empty()) break;
		Node tmp = Q.top();
		j += tmp.fuel;
		Q.pop();
		ans++;
	}
	if (j < L) cout << -1 << endl;
	else cout << ans << endl;
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d%d", &G[i].dis, &G[i].fuel);
		scanf("%d%d", &L, &P);
		for (int i = 0; i < N; i++)
			G[i].dis = L - G[i].dis;
		sort(G, G + N, cmp);
		solve();
	}
	return 0;
}
