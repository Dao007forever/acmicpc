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

const int MAXN = 55;
struct Edge
{
	int v, next;
}edge[MAXN * MAXN];
struct Set
{
	int h, n;
	int num[MAXN];
}S[MAXN];
int N, num, Top, Size, Index;
int Head[MAXN], Stack[MAXN], dfn[MAXN], low[MAXN], id[MAXN], vis[MAXN];
int in[MAXN];

void addEdge(int u, int v)
{
	//cout << u << " " << v << endl;
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

bool cmp(Set a, Set b)
{
	return a.h < b.h;
}

void Tarjan(int u)
{
	low[u] = dfn[u] = ++Index;
	Stack[++Top] = u;
	vis[u] = 1;
	for (int i = Head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].v;
		if (!dfn[v])
		{
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u])
	{
		Size++;
		for (; Stack[Top + 1] != u; --Top)
		{
			vis[Stack[Top]] = 0;
			id[Stack[Top]] = Size;
		}
	}
}


void init()
{
	num = Index = Top = Size = 0;
	memset(Head, -1, sizeof(Head));
	memset(Stack, 0, sizeof(Stack));
	memset(vis, 0, sizeof(vis));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(in, 0, sizeof(in));
	memset(id, 0, sizeof(id));
}

void output()
{
	for (int i = 1; i <= Size; i++)
		for (int j = 0; j < S[i].n; j++)
		{
			char ch = 'A' + S[i].num[j] - 1;
			if (j != S[i].n - 1) printf("%c ", ch);
			else printf("%c\n", ch);
		}
}

int main()
{
	freopen("a", "r", stdin);
	bool blank = false;
	while (scanf("%d", &N) && N)
	{
		init();

		if (blank)
		{
			printf("\n");
		}
		blank = true;
		for (int i = 1; i <= N; i++)
		{
			string s;
			char str[10][10];
			getline(cin, s);
			istringstream ss(s);
			for (int k = 0; k < 6; k++)
			{
				cin >> str[k];
				in[str[k][0] - 'A' + 1] = 1;
			}
			for (int k = 0; k < 5; k++)
			if (str[k][0] != str[5][0])
			{
				addEdge(str[5][0] - 'A' + 1, str[k][0] - 'A' + 1);
			}
		}
		for (int i = 1; i <= 26; i++)
		if (in[i] && !dfn[i]) Tarjan(i);
		
		memset(S, 0, sizeof(S));
		for (int i = 1; i <= 26; i++)
		if (in[i])
		{
			S[id[i]].num[S[id[i]].n++] = i;
		}
		for (int i = 1; i <= Size; i++)
		{
			int len = S[i].n;
			for (int j = 0; j < len; j++)
				for (int k = j + 1; k < len; k++)
					if (S[i].num[k] < S[i].num[j])
					{
						int tmp = S[i].num[k];
						S[i].num[k] = S[i].num[j];
						S[i].num[j] = tmp;
					}
			S[i].h = S[i].num[0];
		}
		sort(S + 1, S + Size + 1, cmp);

		output();
	}
	return 0;
}
