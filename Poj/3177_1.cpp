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

const int maxn = 5000 + 10;
const int maxm = 10000 + 10;
struct Nod
{
	int b, nxt;
	void init(int b, int nxt)
	{
		this->b = b;
		this->nxt = nxt;
	}
};
struct BCC
{
	int E[maxn]; int n;
	Nod buf[maxm * 2]; int len;

	bool brg[maxm * 2];
	bool cut[maxn];
	int id[maxn];

	int EBcc[maxn]; int nBcc;
	Nod bufBcc[maxn * 2]; int lenBcc;
	int tot[maxn];

	char vis[maxn];

	void init(int n)
	{
		this->n = n;
		memset(E, 255, sizeof(E));
		len = 0;
	}

	void addEdge(int a, int b)
	{
		buf[len].init(b, E[a]); E[a] = len++;
		buf[len].init(a, E[b]); E[b] = len++;
	}

	void dfs(int idx, int father, int deep)
	{
		static int D[maxn];
		static int anc[maxn];

		vis[idx] = 1;
		D[idx] = anc[idx] = deep;
		int tot = 0;
		for (int i = E[idx]; i != -1; i = buf[i].nxt)
		{
			int b = buf[i].b;
			if (vis[b] == 1 && father != b)
				anc[idx] = min(anc[idx], D[b]);
			if (vis[b] == 0)
			{
				dfs(b, idx, deep + 1);
				tot++;
				anc[idx] = min(anc[idx], anc[b]);
				if ((deep == 0 && tot > 1) || (deep != 0 && anc[b] >= D[idx]))
					cut[idx] = true;
				if (anc[b] > D[idx])
					brg[i] = brg[i ^ 1] = true;
			}
		}
		vis[idx] = 2;
	}

	void floodFill(int idx)
	{
		id[idx] = nBcc;
		for (int i = E[idx]; i != -1; i = buf[i].nxt)
		{
			if (id[buf[i].b] == -1 && brg[i] == false)
				floodFill(buf[i].b);
		}
	}

	void solve()
	{
		memset(vis, 0, sizeof(vis));
		memset(cut, 0, sizeof(cut));
		memset(brg, 0, sizeof(brg));
		memset(id, 255, sizeof(id));
		memset(tot, 0, sizeof(tot));
		memset(EBcc, 255, sizeof(EBcc));
		nBcc = lenBcc = 0;
		for (int i = 0; i < n; i++)
			if (vis[i] == 0) dfs(i, i, 0);
		for (int i = 0; i < n; i++)
			if (id[i] == -1) floodFill(i), nBcc++;
		for (int i = 0; i < n; i++)
			tot[id[i]]++;
		for (int j = 0; j < n; j++)
		{
			int a = id[j];
			for (int i = E[j]; i != -1; i = buf[i].nxt)
			{
				int b = id[buf[i].b];
				if (brg[i] && a < b)
				{
					bufBcc[lenBcc].init(b, EBcc[a]); EBcc[a] = lenBcc++;
					bufBcc[lenBcc].init(a, EBcc[b]); EBcc[b] = lenBcc++;
				}
			}
		}
	}
}bcc;

int main()
{
	freopen("a", "r", stdin);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		bcc.init(n);
		int a, b;
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d", &a, &b);
			bcc.addEdge(a - 1, b - 1);
		}
		bcc.solve();
		int count = 0;
		for (int i = 0; i < bcc.nBcc; i++)
			if (bcc.EBcc[i] != -1 && bcc.bufBcc[bcc.EBcc[i]].nxt == -1) count++;
		printf("%d\n", (count + 1) / 2);
	}
	return 0;
}
