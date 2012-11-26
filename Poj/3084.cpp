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
const int inf = 0x3f3f3f3f;
struct SAP
{
	int cap[MAXN][MAXN], flow[MAXN][MAXN];
	int n;
	int h[MAXN], vh[MAXN], source, sink;
	void init(int n)
	{
		this->n = n;
		memset(cap, 0, sizeof(cap));
	}
	void addCap(int i, int j, int val)
	{
		cap[i][j] += val;
	}
	int sap(const int idx, const int maxCap)
	{
		if (idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for (int i = 0; i < n; i++)
		{
			if (cap[idx][i] - flow[idx][i] > 0)
			{
				if (h[idx] == h[i] + 1)
				{
					d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
					flow[idx][i] += d;
					flow[i][idx] -= d;
					l -= d;
					if (h[source] == n || l == 0) return maxCap - l;
				}
				minH = min(minH, h[i] + 1);
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
		this->sink = sink;
		this->source = source;
		memset(flow, 0, sizeof(flow));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
};
SAP sap;
int N, M;

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &M, &N);
		int source = M, sink = N;
		sap.init(M + 1);
		for (int i = 0; i < M; i++)
		{
			char str[10];
			int num;
			scanf("%s %d\n", str, &num);
			if (str[0] == 'I') 
			{
				sap.addCap(source, i, inf);
				//cout << "source " << i << " " << inf << endl;
			}
			for (int j = 1; j <= num; j++)
			{
				int k;
				scanf("%d", &k);
				sap.addCap(i, k, inf);
				sap.addCap(k, i, 1);
				//cout << i << " " << k << " " << inf << endl;
				//cout << k << " " << i << " " << 1 << endl;
			}
		}
		int tmp = sap.solve(source, sink);
		if (tmp >= inf) printf("PANIC ROOM BREACH\n");
		else printf("%d\n", tmp);
	}
	return 0;
}
