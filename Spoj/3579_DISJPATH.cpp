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

#define th(x) this->x = x
const int MAXN = 10000 + 10;
const int MAXM = 500000 + 10;
const int inf = 0x3f3f3f3f;

int N, K;
char tmp[MAXN];

struct Nod
{
        int b, next;
        int cap, flow;
        void init(int b, int cap, int next)
        {
                th(b);
                th(cap);
                th(next);
        }
};
struct SAP
{
        int E[MAXN], n;
        int h[MAXN], vh[MAXN], source, sink;
        Nod buf[MAXM * 4]; int len;
		int queue[MAXN];
        void init(int n)
        {
                this->n = n;
                len = 0;
                memset(E, 255, sizeof(E));
        }
        void addCap(int i, int j, int cap1, int cap2 = 0)
        {
                buf[len].init(j, cap1, E[i]);
                E[i] = len++;
                buf[len].init(i, cap2, E[j]);
                E[j] = len++;
        }
        int sap(const int idx, const int maxCap)
        {
                if (idx == sink)
                        return maxCap;
                int l = maxCap, d, minH = n;
                for (int i = E[idx]; i != -1; i = buf[i].next)
                {
                        Nod & nod = buf[i];
                        if (nod.cap-nod.flow > 0)
                        {
                                if (h[idx] == h[nod.b] + 1)
                                {
                                        d = sap(nod.b, min(l, nod.cap - nod.flow));
                                        nod.flow += d;
                                        buf[i ^ 1].flow -= d;
                                        l -= d;
                                        if (h[source] == n || l == 0) return maxCap - l;
                                }
                                minH = min(minH, h[nod.b] + 1);
                        }
                }
                if (l == maxCap)
                {
                        vh[h[idx]]--;
                        vh[minH]++;
                        if (vh[h[idx]] == 0)
                                h[source] = n;
                        h[idx] = minH;
                }
                return maxCap - l;
        }
        int solve(int source, int sink)
        {
                if (source == sink) return inf;
                th(source); th(sink);
                memset(h, 0, sizeof(h));
                memset(vh, 0, sizeof(vh));
                for (int i = 0; i < len; i++)
                        buf[i].flow = 0;
                int ans = 0;
                while (h[source] != n)
                        ans += sap(source, inf);
                return ans;
        }
		void output()
		{
			for (int i = 0; i < K; i++)
			{
				int r = 0;
				queue[r] = 1;
				while (queue[r] != 2)
				{
					int idx = queue[r];
					for (int i = E[idx]; i != -1; i = buf[i].next)
					if (buf[i].flow == 1)
					{
						queue[++r] = buf[i].b;
						buf[i].flow = 0;
						break;
					}
				}
				printf("1");
				for (int j = 1; j <= r; j++)
				if (queue[j] <= N)
					printf(" %d", queue[j]);
				printf("\n");
			}
			printf("\n");
		}
		void test()
		{
			for (int i = 0; i < len; i++)
			if (buf[i].flow == 1)
				printf("%d\n", buf[i].b);
		}
}sap;

int main()
{
	freopen("in", "r", stdin);
//	freopen("out1", "w", stdout);
	int cas = 1;
	while (scanf("%d%d", &K, &N))
	{
		if (K == 0 && N == 0) break;
		printf("Case %d:\n", cas++);
		sap.init(2 * N);
		int source = 0, sink = 2 * N - 1;

		gets(tmp);
		for (int i = 1; i <= N; i++)
		{
			gets(tmp);
			for (int j = 0; tmp[j] != '\0'; j++)
			if (tmp[j] >= '0' && tmp[j] <= '9')
			{
				int k = 0;
				while (tmp[j] >= '0' && tmp[j] <= '9')
					k = k * 10 + tmp[j++] - '0';
				if (i == 1) 
				{
					sap.addCap(i, k, 1);
//cout << i << " " << k << " 1" << endl;
				}
				else if (i == 2)
				{
					sap.addCap(k + N - 2, i, 1);
//cout << k + N - 2 << " " << i << " 1" << endl;
				}
				else
				{
				//	if (k > i)
					{
						sap.addCap(i + N - 2, k, 1);
//cout << i + N - 2 << " " << k << " 1" << endl;
					}
				}
				while (tmp[j] == ' ') j++;
				j--;
			}
		}
		for (int i = 3; i <= N; i++)
		{
			sap.addCap(i, i + N - 2, 1);
//cout << i << " " << i + N << " 1" << endl;
		}
		sap.addCap(source, 1, K);
		sap.addCap(2, sink, K);
//cout << source << " 1 " << K << endl;
//cout << "2 " << sink << " " << K << endl;
		int ans = sap.solve(source, sink);
//sap.test();
		if (ans >= K)
		{
			sap.output();
		}
		else printf("Impossible\n");
	}
	return 0;
}
