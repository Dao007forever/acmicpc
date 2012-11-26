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

const int maxn = 26;
const int inf = 100000000;
int adj[33][33];
int deg[33];
long long sum;
vector<int> v;

void Floyd() {
	for (int k = 0; k < maxn; k++)
		for (int i = 0; i < maxn; i++)
			for (int j = 0; j < maxn; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

void solve() {
	Floyd();
	int cnt = 0, a, b;
	for (int i = 0; i < maxn; i++)
		if (deg[i] & 1) {
			cnt++;
			v.push_back(i);
		}
	if (cnt == 2) {
		cout << sum + adj[v[0]][v[1]] << endl;	
	} else {
		cout << sum << endl;
	}
}

int main() {
	freopen("in", "r", stdin);
	char str[111111];
	sum = 0;
	while (scanf("%s", str) != EOF) {
		if (strcmp(str, "deadend") == 0) {
			solve();
			for (int i = 0; i < maxn; i++)
				for (int j = 0; j < maxn; j++)
					if (i != j) adj[i][j] = inf;
			memset(deg, 0, sizeof(deg));
			sum = 0;
			v.clear();
			continue;
		} else {
			int len = strlen(str);
			int a = str[0] - 'a', b = str[len - 1] - 'a';
			adj[a][b] = adj[b][a] = len;
			deg[a]++; deg[b]++;
			sum += len;
		}
	}
	return 0;
}
