/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 03:48:04 PM UTC
 * File Name: B.cpp
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

#define inf 10000000
int n, r;
map<pair<int, int>, int> dis;
map<pair<int, int>, int> pre;
map<pair<int, int>, int> f;

void output(pair<int, int> x) {
	if (pre[x] == 0) {
		output(MP(x.first - x.second, x.second));
		printf("T");
	} else {
		output(MP(x.first, x.second - x.first));
		printf("B");
	}
}

int main() {
	cin >> n >> r;
	queue<pair<int, int> > q;
	q.push(MP(1, 1));
	dis[MP(1, 1)] = 1;
	f[MP(1, 1)] = 0;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int d = dis[cur];
		if (d == n) break;
		pair<int, int> nxt;
		nxt.first = cur.first + cur.second;
		nxt.second = cur.second;
		//'T'
		if (nxt.first <= r && (dis.find(nxt) == dis.end() || dis[nxt] > dis[cur] + 1)) {
			dis[nxt] = dis[cur] + 1;
			pre[nxt] = 0;
			if (pre[nxt] == pre[cur]) {
				if (f.find(nxt) == f.end() || f[cur] + 1 < f[nxt])
					f[nxt] = f[cur] + 1;
			} else {
				if (f.find(nxt) == f.end() || f[cur] < f[nxt])
					f[nxt] = f[cur];
			}
			q.push(nxt);
		}
		
		//'B'
		nxt.first = cur.first;
		nxt.second = cur.first + cur.second;
		if (nxt.second <= r && (dis.find(nxt) == dis.end() || dis[nxt] > dis[cur] + 1)) {
			dis[nxt] = dis[cur] + 1;
			pre[nxt] = 1;
			if (pre[nxt] == pre[cur]) {
				if (f.find(nxt) == f.end() || f[cur] + 1 < f[nxt])
					f[nxt] = f[cur] + 1;
			} else {
				if (f.find(nxt) == f.end() || f[cur] < f[nxt])
					f[nxt] = f[cur];
			}
			q.push(nxt);
		}
	}
	int Min = inf;
	pair<int, int> ret;
	for (int i = 1; i <= r; i++) {
		pair<int, int> tmp = MP(i, r);
		if (f.find(tmp) != f.end()) {
			if (f[tmp] < Min) {
				Min = inf;
				ret = tmp;
			}
		}
		tmp = MP(r, i);
		if (f.find(tmp) != f.end()) {
			if (f[tmp] < Min) {
				Min = inf;
				ret = tmp;
			}
		}
	}
	if (Min == inf) {
		puts("IMPOSSIBLE");
		return 0;
	}
	printf("%d\n", f[ret]);
	printf("T");
	output(ret);
	return 0;
}

