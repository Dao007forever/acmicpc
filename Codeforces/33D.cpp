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

struct Point {
	LL x, y;
}p[1111];
struct Circle {
	LL x, y, r;
}c[1111];
bool adj[1005][1005];
int n, m, k;

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	for (int i = 0; i < m; i++)
		cin >> c[i].r >> c[i].x >> c[i].y;

	memset(adj, 0, sizeof(adj));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			LL dx = (p[i].x - c[j].x) * (p[i].x - c[j].x);
			LL dy = (p[i].y - c[j].y) * (p[i].y - c[j].y);
			if (dx + dy < c[j].r * c[j].r)
				adj[i][j] = true;
		}

	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		int ret = 0;
		for (int j = 0; j < m; j++)
			ret += adj[a][j] ^ adj[b][j];
		cout << ret << endl;
	}
	return 0;
}
