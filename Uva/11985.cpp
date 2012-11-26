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
#define maxV 40005
#define maxE 400*maxV
int n;
int idx[500005], cnt[500005];
int a[maxV];
vector<int> p;

void getPrime() {
	vector<bool> vis(8000);
	for (int i = 2; i <= 7200; i++)
		if (!vis[i]) {
			p.push_back(i);
			for (int j = 2; i * j <= 7200; j++)
				vis[i * j] = true;
		}
}

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
	getPrime();
	for (int i = 2; i <= 500000; i++) {
		for (int j = 0; j < p.size() && p[j] <= i; j++) {
			if (i % p[j] == 0) {
				cnt[i] += cnt[i / p[j]] + 1;
				break;
			}
		}
		if (!cnt[i]) cnt[i] = 1;
	}
	for (int cas = 1; Test--; cas++) {
		memset(idx, -1, sizeof(idx));
		printf("Case %d: ", cas);
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			idx[a[i]] = i;
		}
		mf.init(n + 2);
		int source = n, sink = n + 1;
		for (int i = 0; i < n; i++) {
			int x = a[i];
			if (cnt[x] & 1) mf.addCap(source, i, 1);
			else mf.addCap(i, sink, 1);
			for (int j = 0; j < p.size() && p[j] <= x; j++) {
				if (x % p[j]) continue;
				int y = x / p[j];
				if (idx[y] != -1) {
					int v = idx[y];
					if (cnt[x] & 1) {
						mf.addCap(i, v, 1);
					} else {
						mf.addCap(v, i, 1);
					}
				}
				if (y > p[p.size() -1] && cnt[y] == 1) {
					y = p[j];
					if (idx[y] != -1) {
						int v = idx[y];
						if (cnt[x] & 1) {
							mf.addCap(i, v, 1);
						} else {
							mf.addCap(v, i, 1);
						}
					}
				}
			}
		}
		int ret = mf.solve(source, sink);
		printf("%d\n", n - ret);
	}
	return 0;
}