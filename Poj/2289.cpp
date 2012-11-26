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
const int MAXN = 2000 + 10;
const int MAXM = 500000 + 10;
const int inf = 0x3f3f3f3f;
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
}sap;
int N, M;
vector<int> vec[MAXN];

bool check(int lim)
{
	int source = 0, sink = N + M + 1;
	sap.init(N + M + 2);
	for (int i = 1; i <= N; i++)
	{
		sap.addCap(source, i, 1);
		//cout << "source " << i << " 1" << endl;
		for (int j = 0; j < vec[i].size(); j++)
		{
			sap.addCap(i, vec[i][j], 1);
			//cout << i << " " << vec[i][j] << " 1" << endl;
		}
	}
	for (int i = 1; i <= M; i++)
	{
		sap.addCap(N + i, sink, lim);
		//cout << N + i << " sink " << lim << endl;
	}
	int tmp = sap.solve(source, sink);
	return tmp == N;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d\n", &N, &M))
	{
		if (N == 0 && M == 0) break;
		for (int i = 1; i <= N; i++)
			vec[i].clear();
		for (int i = 1; i <= N; i++)
		{
			string s, name;
			getline(cin, s);
			istringstream ss(s);
			ss >> name;
			int k;
			while (ss >> k)
			{
				vec[i].push_back(N + k + 1);
			}
		}
		int Left = 0, Right = N, ans;
		while (Left <= Right)
		{
			int Mid = (Left + Right) / 2;
			if (check(Mid))
			{
				Right = Mid - 1;
				ans = Mid;

			}
			else Left = Mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
