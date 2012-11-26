/*
 * 差分约束，但是要注意，题目中的关系是Ssi+ni+1 - Ssi > k或者Ssi+ni+1 - Ssi < k，而差分约束的条件是要>=或者<=，考虑到都是整数，所以可以这样变形：将Ssi+ni+1 - Ssi > k变形为Ssi+ni+1 - Ssi >= k+1，将Ssi+ni+1 - Ssi < k变形为Ssi+ni+1 - Ssi <= k-1，然后bellman_ford判断是否有负环即可。
 */
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

#define MAXN 105
int N, M;
vector<pair<int, int> > adj[MAXN];
int dist[MAXN];

bool bellman_ford() {
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i <= N + 1; i++) {
		bool relaxed = false;
		for (int p = 0; p <= N + 1; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int q = adj[p][j].first, tmp = dist[p] + adj[p][j].second;
				if (tmp < dist[q]) {
					dist[q] = tmp;
					relaxed = true;
				}
			}
		if (!relaxed) return true;
	}
	return false;
}

int main() {
	freopen("in", "r", stdin);
	while (cin >> N && N) {
		for (int i = 0; i <= N + 1; i++)
			adj[i].clear();
		for (int i = 1; i <= N + 1; i++)
			adj[0].push_back(make_pair(i, 0));
		cin >> M;
		while (M--) {
			int s, n, k;
			char op[5];
			scanf("%d %d %s %d", &s, &n, op, &k);
			if (*op == 'g') {
				adj[s + n + 1].push_back(make_pair(s, -(k + 1)));
			} else {
				adj[s].push_back(make_pair(s + n + 1, k - 1));
			}
		}
		if (bellman_ford()) cout << "lamentable kingdom" << endl;
		else cout << "successful conspiracy" << endl;
	}
	return 0;
}
