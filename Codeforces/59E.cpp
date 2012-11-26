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

map<pair<int, int>, set<int> > forb;
char vis[3100][3100];
struct Edge
{
	int u, v, w, next;
}edge[120000];
int Head[5555], num;

void addEdge(int u, int v, int w)
{
	edge[num].u = u;
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}
int N, M, K;
struct Node
{
	int u, v, w;
	int op, pre;
	Node(){}
	Node(int a, int s, int d, int r, int t)
	{
		u = a;
		v = s;
		w = d;
		op = r;
		pre = t;
	}
};
Node que[12000000];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &N, &M, &K);
	num = 0;
	memset(Head, -1, sizeof(Head));
	for (int i = 0; i < M; i++)
	{
		int u, v, w;
		scanf("%d%d", &u, &v);
		addEdge(u, v, 1);
		addEdge(v, u, 1);
	}
	for (int i = 0; i < K; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		pair<int, int>pr = make_pair(a, b);
		if (forb.find(pr) == forb.end())
		{
			set<int>tmp;
			tmp.insert(c);
			forb[pr] = tmp;
		}
		else
		{
			forb[pr].insert(c);
		}
	}
	int headq = 0, tailq = 0;
	que[tailq++] = Node(0, 1, 0, 1, -1);
	vis[0][1] = 1;
	int k = -1;
	while (headq < tailq)
	{
		Node tmp = que[headq++];
		int u = tmp.u, v = tmp.v, w = tmp.w;
		if (v == N)
		{
			k = headq - 1;
			printf("%d\n", w);
			break;
		}
		for (int i = Head[v]; i != -1; i = edge[i].next)
		{
			if (forb[make_pair(u, v)].find(edge[i].v) != forb[make_pair(u, v)].end())
				continue;
			if (!vis[v][edge[i].v])
			{
				vis[v][edge[i].v] = 1;
				que[tailq++] = Node(v, edge[i].v, w + 1, edge[i].v, headq - 1);
			}
		}
	}
	if (k == -1)
	{
		printf("-1\n");
		return 0;
	}
	vector<int> ans;
	while (k != -1)
	{
		ans.push_back(que[k].op);
		k = que[k].pre;
	}
	reverse(ans.begin(), ans.end());
	printf("%d", ans[0]);
	for (int i = 1; i < ans.size(); i++)
		printf(" %d", ans[i]);
	return 0;
}

