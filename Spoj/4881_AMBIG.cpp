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

const int maxn = 2005;
struct state {
	int u, v, w;
};
struct Edge {
	int v, next, w;
}edge[maxn * maxn * 2];
int num, Head[maxn];
int N, M;
bool dp[maxn][maxn][2];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main()
{
	freopen("in", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	scanf("%d%d", &M, &N);
	for (int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
	}

	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	queue<state> Q;
	state st;
	st.u = 0; st.v = 0; st.w = 0;
	Q.push(st);
	while (!Q.empty()) {
		state cur = Q.front();
		Q.pop();
		int u = cur.u, v = cur.v, w = cur.w;
		if (u == v && u == 1 && w) {
			puts("YES");
			return 0;
		}
		for (int i = Head[u]; i != -1; i = edge[i].next)
			for (int j = Head[v]; j != -1; j = edge[j].next)
				if (edge[i].w == edge[j].w) {
					int ww = w | (i != j);
					if (!dp[edge[i].v][edge[j].v][ww]) {
						dp[edge[i].v][edge[j].v][ww] = 1;
						state tmp;
						tmp.u = edge[i].v;
						tmp.v = edge[j].v;
						tmp.w = ww;
						Q.push(tmp);
					}
				}
	}
	puts("NO");
	return 0;
}
