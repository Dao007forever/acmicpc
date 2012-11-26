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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

typedef int F;
#define inf (1 << 29)
#define maxV 610
#define maxE 400000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, F f) {
		//cout << x << " " << y << " " << f << endl;
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	bool bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return (level[t] != -1);
	}

	F dfs(int v, int t, F f) {
		if (v == t) return f;
		for (int i = used[v]; i != -1; used[v] = i = prev[i])
			if (level[to[i]] > level[v] && cap[i] > flow[i]) {
				F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}

	F solve(int s, int t) {
		while (bfs(s, t)) {
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return ans;
	}
}mf;

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int r, c;
		scanf("%d%d", &r, &c);
		mf.init(r*c + r + c + 2);
		int source = r*c + r + c, sink = r*c + r + c + 1;
		int sum = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				int x;
				scanf("%d", &x);
				sum += x;
				mf.addCap(source, i * c + j, x);
				mf.addCap(i * c + j, r * c + i, inf);
				mf.addCap(i * c + j, r * c + r + j, inf);
			}
		}
		int d;
		scanf("%d", &d);
		while (d--) {
			int r1, c1, r2, c2;
			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			//mf.addCap(r1 * c + c1, r * c + r2, inf);
			//mf.addCap(r1 * c + c1, r * c + r + c2, inf);
			//mf.addCap(r2 * c + c2, r * c + r1, inf);
			//mf.addCap(r2 * c + c2, r * c + r + c1, inf);
			mf.addCap(r1 * c + c1, r2 * c + c2, inf);
			mf.addCap(r2 * c + c2, r1 * c + c1, inf);
		}
		for (int i = 0; i < r; i++) {
			int x;
			scanf("%d", &x);
			mf.addCap(r * c + i, sink, x);
		}
		for (int i = 0; i < c; i++) {
			int x;
			scanf("%d", &x);
			mf.addCap(r * c + r + i, sink, x);
		}
		int ret = mf.solve(source, sink);
		printf("%s\n", ret == sum ? "Yes" : "No");
	}
	return 0;
}