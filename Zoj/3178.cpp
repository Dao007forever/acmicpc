#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
#define maxn 100 + 10
const double inf = 1e5;
int n, m;
double ans[maxn], money[maxn];
int ind[maxn][maxn];
int sell[maxn], app[maxn];
vector<int> v[maxn];
double dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

struct SAP
{
	double cap[maxn][maxn], flow[maxn][maxn];
	int n;
	int h[maxn], vh[maxn], source, sink;
	
	int app[maxn];

	void init(int n)
	{
		this->n = n;
		memset(cap, 0, sizeof(cap));
	}
	void addCap(int i, int j, double val)
	{
		cap[i][j] += val;
	}

	double sap(const int idx, const double maxCap)
	{
		if(idx == sink)
			return maxCap;
		double l = maxCap, d;
		int minH = n;

		for(int i = 0; i < n; i ++)
		{
			if(dblcmp(cap[idx][i]-flow[idx][i]) > 0)
			{
				if(h[idx]==h[i]+1)
				{
					d = sap(i, min(l, cap[idx][i]-flow[idx][i]));
					flow[idx][i] += d;
					flow[i][idx] -= d;
					l -= d;
					if(h[source] == n || dblcmp(l) == 0) return maxCap-l;
				}
				minH = min(minH, h[i]+1);
			}
		}
		if(dblcmp(l - maxCap) == 0)
		{
			vh[h[idx]]--;
			vh[minH]++;
			if(vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	double solve(int source, int sink)
	{
		if(source == sink)	return inf;
		this->sink = sink;
		this->source = source;
		memset(flow, 0, sizeof(flow));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		double ans = 0.0;
		while(h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
	
	void dfs(int x) {
		app[x] = true;
		for (int i = 0; i < v[x].size(); i++) {
			int y = v[x][i];
			if (!app[y] && dblcmp(cap[y][x] - flow[y][x]) > 0) 
				dfs(y);
		}
	}
}sap;

void solve() {
	int source = 0, sink = n + m + 1;
	while (1) {
		sap.init(n + m + 2);
		for (int i = 0; i <= n + m + 2; i++)
			v[i].clear();
		for (int i = 1; i <= n; i++)
		if (sell[i] != 0) {
			v[source].push_back(i);
			v[i].push_back(source);
		}
		for (int i = 1; i <= m; i++) {
			if (dblcmp(money[i]) != 0) {
				v[i + n].push_back(sink);
				v[sink].push_back(i + n);
				//sap.addCap(i + n, sink, money[i]);
				sap.cap[i + n][sink] = money[i];
				for (int j = 1; j <= ind[i][0]; j++)
				if (sell[ind[i][j]] != 0) {
					v[ind[i][j]].push_back(i + n);
					v[i + n].push_back(ind[i][j]);
					//sap.addCap(ind[i][j], i + n, inf);
					sap.cap[ind[i][j]][i + n] = inf;
				}
			}
		}
		
		double l = 0, r = 31.0 * 60000, tmp, mid;
		while (r - l > eps) {
			mid = (l + r) / 2.0;
			memset(sap.flow, 0, sizeof(sap.flow));
			tmp = 0;
			for (int i = 1; i <= n; i++) 
			if (sell[i] != 0) {
				//sap.addCap(source, i, mid * sell[i]);
				sap.cap[source][i] = mid * sell[i];
				tmp += sap.cap[source][i];
			}
			double maxflow = sap.solve(source, sink);
			if (dblcmp(maxflow - tmp) >= 0) l = mid;
			else r = mid;
		}
		mid = r;
		memset(sap.flow, 0, sizeof(sap.flow));
		for (int i = 1; i <= n; i++)
		if (sell[i] != 0) {
			sap.cap[source][i] = mid * sell[i];
		}
		double maxflow = sap.solve(source, sink);
		memset(sap.app, 0, sizeof(sap.app));
		sap.dfs(sink);
		double t1 = 0, t2 = 0;
		for (int i = 1; i <= n; i++)
		if (!sap.app[i] && sell[i] != 0) {
			t2 += sell[i];
			for (int j = 1; j <= m; j++)
				for (int k = 1; k <= ind[j][0]; k++)
				if (ind[j][k] == i) {
					t1 += money[j];
					money[j] = 0;
				}
		}
		double tans = t1 / t2;
		for (int i = 1; i <= n; i++)
		if (!sap.app[i] && sell[i] != 0) {
			sell[i] = 0;
			ans[i] = tans;
		}
		bool flag = true;
		for (int i = 1; i <= n; i++)
		if (sell[i] != 0) {
			flag = false;
		}
		if (flag) break;
	}
	for (int i = 1; i < n; i++)
		printf("%.4lf ", ans[i]);
	printf("%.4lf\n", ans[n]);
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(app, 0, sizeof(app));
		memset(ind, 0, sizeof(ind));
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &sell[i]);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%lf", &money[i]);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d", &ind[i][0]);
			for (int j = 1; j <= ind[i][0]; j++) {
				scanf("%d", &ind[i][j]);
				app[ind[i][j]] = true;
			}
		}
		bool flag = false;
		for (int i = 1; i <= n; i++) 
		if (!app[i]) {
			puts("Impossible");
			flag = true;
			break;
		}
		if (flag) continue;
		solve();
	}
	return 0;
}