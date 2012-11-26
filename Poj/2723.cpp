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

const int MAXN = 3000 + 10;
const int MAXM = 6000 + 10;
struct Node
{
        int b, nxt;
        void init(int b, int nxt)
        {
                this->b = b;
                this->nxt = nxt;
        }
};

struct Kosaraju
{
        int E[MAXN], EN[MAXN]; int n;
        Node buf[MAXM * 2]; int len;

        int id[MAXN];
        int nScc;

        int vis[MAXN];
        int order[MAXN], order_idx;

        void init(int n)
        {
                this->n = n;
                memset(E, 255, sizeof(E));
                memset(EN, 255, sizeof(EN));
                len = 0;
        }

        void addEdge(int a, int b)
        {
                buf[len].init(b, E[a]); E[a] = len++;
                buf[len].init(a, EN[b]); EN[b] = len++;
        }

        void dfs(int idx)
        {
                if (vis[idx]) return;
                vis[idx] = true;
                for (int i = E[idx]; i != -1; i = buf[i].nxt)
                        dfs(buf[i].b);
                order[order_idx++] = idx;
        }

        void ndfs(int idx)
        {
                if (vis[idx]) return;
                vis[idx] = true;
                id[idx] = nScc;
                for (int i = EN[idx]; i != -1; i = buf[i].nxt)
                        ndfs(buf[i].b);
        }

        void solve()
        {
                memset(vis, 0, sizeof(vis));
                order_idx = nScc = 0;
                for (int i = 0; i < n; i++)
                        dfs(i);
                memset(vis, 0, sizeof(vis));
                for (int i = n - 1; i >= 0; i--)
                if (vis[order[i]] == false) 
                {
                        ndfs(order[i]);
                        nScc++;
                }
        }

        int partner[MAXN], stack[MAXN];
        int ENScc[MAXN];
        Node bufNScc[MAXM]; int lenNScc;

        bool sat()
        {
                solve();
                for (int i = 0; i < n; i += 2)
                {
                        if (id[i] == id[i + 1]) return false;
                }
                return true;
        }
}Ts;

int n, m;
int addr[MAXN], A[MAXN], B[MAXN];

int partner(int x)
{
	if (x & 1) return x - 1;
	return x + 1;
}

bool check(int lim)
{
	Ts.init(2 * n);
	for (int i = 0; i < lim; i++)
	{
		Ts.addEdge(partner(A[i]), B[i]);
		Ts.addEdge(partner(B[i]), A[i]);
	}
	return Ts.sat();
}

void solve()
{
	int Left = 0, Right = m + 1;
	while (Left < Right - 1)
	{
		int Mid = (Left + Right) / 2;
		if (check(Mid)) Left = Mid;
		else Right = Mid;
	}
	printf("%d\n", Left);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &n, &m) && n || m)
	{
		int a, b, cnt = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &a, &b);
			addr[a] = cnt++;
			addr[b] = cnt++;
		}
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d", &A[i], &B[i]);
			A[i] = addr[A[i]];
			B[i] = addr[B[i]];
		}
		solve();
	}
}
