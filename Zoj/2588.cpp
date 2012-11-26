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

const int MAXN = 10000 + 10;
const int MAXM = 100000 + 10;
struct Node
{
	int j, tag, id;
	Node *next;
};
int n, m;
int nid;
Node mem[MAXM * 2]; int memp;
Node *e[MAXN];

int bridge[MAXM];
int nbridge;
int low[MAXN], dfn[MAXN];
int visited[MAXN];

int AddEdge(Node *e[], int i, int j)
{
	Node *p;
	for (p = e[i]; p != NULL; p = p->next)
	{
		if (p->j == j) break;
	}
	if (p != NULL)
	{
		p->tag++;
		return 0;
	}
	p = &mem[memp++];
	p->j = j; p->next = e[i]; e[i] = p; p->id = nid; p->tag = 0;
	return 1;
}

void DFS(int i, int father, int dth)
{
	visited[i] = 1; dfn[i] = low[i] = dth;
	Node *p;
	for (p = e[i]; p != NULL; p = p->next)
	{
		int j = p->j;
		if (j != father && visited[j] == 1)
			low[i] = min(low[i], dfn[j]);
		if (visited[j] == 0)
		{
			DFS(j, i, dth + 1);
			low[i] = min(low[i], low[j]);
			if (low[j] > dfn[i] && !p->tag)
				bridge[p->id] = ++nbridge;
		}
	}
	visited[i] = 2;
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		memp = 0; nid = 0;
		memset(e, 0, sizeof(e));
		for (int k = 0; k < m; k++, nid++)
		{
			int i, j;
			scanf("%d%d", &i, &j);
			AddEdge(e, i - 1, j - 1);
			AddEdge(e, j - 1, i - 1);
			bridge[nid] = 0;
		}
		nbridge = 0;
		memset(visited, 0, sizeof(visited));
		DFS(0, -1, 1);
		printf("%d\n", nbridge);
		for (int i = 0, k = nbridge; i < m; i++)
		{
			if (bridge[i])
			{
				printf("%d", i + 1);
				if (--k) printf(" ");
			}
		}
		if (nbridge) puts("");
		if (T) puts("");
	}
	return 0;
}
