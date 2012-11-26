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

const int inf = 1000000000;
int n, m, q;
map<string, int> mp;
int u[11111], v[11111], w[11111];
int dist[111][111];

void bellman_ford(int s) {
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			dist[i][j] = inf;
		}
	}
	dist[s][0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int a = u[j], b = v[j], c = w[j];
			if (dist[i - 1][a] + c < dist[i][b]) {
				dist[i][b] = dist[i - 1][a] + c;
			}
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	for (int cas = 1; cas <= Test; cas++) {
		if (cas > 1) puts("");
		printf("Scenario #%d\n", cas);
		mp.clear();
		cin >> n;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			mp[s] = i;
		}
		int s = mp["Calgary"], t = mp["Fredericton"];

		cin >> m;
		for (int i = 0; i < m; i++) {
			string s1, s2;
			cin >> s1 >> s2 >> w[i];
			int a = mp[s1], b = mp[s2];
			u[i] = a; v[i] = b;
		}
		cin >> q;
		bellman_ford(s);
		while (q--) {
			int step;
			cin >> step;
			step++;
			int ret = inf;
			for (int i = 1; i <= min(n, step); i++)
				ret = min(ret, dist[i][t]);
			if (ret == inf) {
				cout << "No satisfactory flights" << endl;
			} else {
				cout << "Total cost of flight(s) is $";
				cout << ret << endl;
			}
		}
	}
	return 0;
}
