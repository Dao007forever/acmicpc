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
int d[111];
int adj[111][111];

int main() {
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		d[a]++;
		d[b]++;
		adj[a][b] = adj[b][a] = 1;
	}

	queue<int> Q;
	int ret = 0;
	while (1) {
		for (int i = 1; i <= n; i++)
			if (d[i] == 1) {
				Q.push(i);
			}
		if (Q.empty()) break;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			d[u]--;
			for (int i = 1; i <= n; i++)
				if (adj[u][i]) {
					adj[u][i] = adj[i][u] = 0;
					d[i]--;
				}
		}
		ret++;
	}	
	cout << ret << endl;
}
