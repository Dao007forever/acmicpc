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
struct Edge {
	int a, b;
	double c;
}e1[100005], e2[100005];
double dist[705];
map<string, int> mp;

void build(double mid) {
	for (int i = 0; i < m; i++) {
		e2[i].a = e1[i].a;
		e2[i].b = e1[i].b;
		e2[i].c = mid - e1[i].c;
	}
}

bool bellman_ford() {
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i < n; i++) {
		bool relaxed = false;
		for (int i = 0; i < m; i++)
			if (dist[e2[i].a] + e2[i].c < dist[e2[i].b]) {
				dist[e2[i].b] = dist[e2[i].a] + e2[i].c;
				relaxed = true;
			}
		if (!relaxed) return false;
	}
	return true;
}

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d", &m) && m) {
		mp.clear();
		n = 0;
		double l = 0, r = 0;
		for (int i = 0; i < m; i++) {
			string s;
			cin >> s;
			string a = s.substr(0, 2);
			string b = s.substr(s.size() - 2, 2);
			if (mp.find(a) == mp.end()) mp[a] = n++;
			if (mp.find(b) == mp.end()) mp[b] = n++;
			int u = mp[a], v = mp[b];
			r = max(r, (double)s.size());
			e1[i].a = u; e1[i].b = v; e1[i].c = s.size();
		}
		bool flag = false;
		double ret;
		while (r - l > 0.001) {
			double mid = (l + r) / 2;
			build(mid);
			if (bellman_ford()) {
				flag = true;
				ret = mid;
				l = mid;
			}
			else r = mid;
		}
		if (!flag) printf("No solution.\n");
		else printf("%.2f\n", ret);
	}
	return 0;
}
