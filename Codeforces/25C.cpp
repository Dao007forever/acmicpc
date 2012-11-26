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

int n;
int dist[333][333];

void Floyd() {
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> dist[i][j];
	long long ret = 0;
	Floyd();
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			ret += (long long)dist[i][j];
	int q;
	cin >> q;
	while (q--) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		if (c >= dist[a][b]) {
			cout << ret << " ";
			continue;
		}
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				int tmp = min(dist[i][a] + dist[b][j] + c, dist[i][b] + dist[a][j] + c);
				if (tmp < dist[i][j]) {
					ret -= dist[i][j] - tmp;
					dist[i][j] = dist[j][i] = tmp;
				}
			}
		cout << ret << " ";
	}
	return 0;
}
