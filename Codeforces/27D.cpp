/*
 * Author : Yang Zhang
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

int n, m;
vector<pair<int, int> > v;
int adj[111][111];
int col[111];
bool ok;

void dfs(int u, int color) {
	if (!ok) return;
	col[u] = color;
	for (int i = 0; i < m; i++)
		if (adj[u][i]) {
			if (!col[i]) dfs(i, 3 - color);
			else if (col[i] == color){
				ok = false;
				return;
			}
		}
}

bool cross(int l1, int r1, int l2, int r2) {
	if (l1 <= l2 && r2 <= r1) return false;
	if (l2 <= l1 && r1 <= r2) return false;
	if (r1 <= l2) return false;
	if (r2 <= l1) return false;
	return true;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		if (l > r) swap(l, r);
		v.PB(MP(l, r));
	}

	memset(adj, 0, sizeof(adj));
	for (int i = 0; i < m; i++)
		for (int j = i + 1; j < m; j++) {
			if (cross(v[i].first, v[i].second, v[j].first, v[j].second))
				adj[i][j] = adj[j][i] = 1;
		}
	memset(col, 0, sizeof(col));
	ok = true;
	for (int i = 0; i < m; i++)
		if (!col[i]) dfs(i, 1);
	if (!ok) cout << "Impossible" << endl;
	else {
		for (int i = 0; i < m; i++)
			if (col[i] == 1) cout << "i";
			else cout << "o";
		cout << endl;
	}
	return 0;
}
