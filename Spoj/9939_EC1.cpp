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
const int MAXM = 200000 + 10;
int N, M;
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
			//cout << a + 1 << " " << b + 1 << endl;
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
}ts;
#define one(x) 2*x+1
#define zero(x) 2*x
int a[MAXN], b[MAXN];

void init()
{
    scanf("%d%d", &N, &M);
	ts.init(2 * N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] == 3) b[i] = 1;
		else b[i] = a[i] + 1;
	}
	for (int i = 1; i <= M; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		x--; y--;
		if (z == 1)
		{
			if (a[x] == a[y])
			{
				ts.addEdge(zero(x), one(y));
				ts.addEdge(zero(y), one(x));
			}
			if (a[x] == b[y])
			{
				ts.addEdge(zero(x), zero(y));
				ts.addEdge(one(y), one(x));
			}
			if (b[x] == a[y])
			{
				ts.addEdge(one(x), one(y));
				ts.addEdge(zero(y), zero(x));
			}
			if (b[x] == b[y])
			{
				ts.addEdge(one(x), zero(y));
				ts.addEdge(one(y), zero(x));
			}
		}
		else
		{
			if (a[x] != a[y])
			{
				ts.addEdge(zero(x), one(y));
				ts.addEdge(zero(y), one(x));
			}
			if (a[x] != b[y])
			{
				ts.addEdge(zero(x), zero(y));
				ts.addEdge(one(y), one(x));
			}
			if (b[x] != a[y])
			{
				ts.addEdge(one(x), one(y));
				ts.addEdge(zero(y), zero(x));
			}
			if (b[x] != b[y])
			{
				ts.addEdge(one(x), zero(y));
				ts.addEdge(one(y), zero(x));
			}
		}
	}
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	int cas = 1;
	while (Test--)
	{
		printf("Case #%d: ", cas++);
		init();
		if (ts.sat()) puts("yes");
		else puts("no");
	}
	return 0;
}
