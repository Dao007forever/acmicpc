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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 100005
int n;
int mk[MAXN], cx[66], cy[MAXN];
vector<int> adj[66];

int path(int u) {
	for (int i = 0, v; i < adj[u].size(); i++) {
		if (!mk[v = adj[u][i]]) {
			mk[v] = 1;
			if (cy[v] == -1 || path(cy[v])) {
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch() {
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	int ret = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (cx[i] == -1) {
			memset(mk, 0, sizeof(mk));
			ret += path(i);
		}
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 0; i < n; i++) {
			int l, r;
			scanf("%d%d", &l, &r);
			for (int j = l; j <= r; j++)
				adj[i].PB(j);
		}
		MaxMatch();
		vector<int> ans;
		for (int i = 0; i < n; i++)
			if (cx[i] != -1) ans.PB(i + 1);
		printf("%d\n", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	}
	return 0;
}