/*
 * Author: Yang Zhang
 * Created Time: Thu 06 Sep 2012 07:41:05 PM CST
 * File Name: 4656_CCROSS.cpp
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

#define MAXN 105
const LL inf = 1ll<<60;
int n;
LL d, h[MAXN];

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%lld", &n, &d);
		vector<LL> p;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &h[i]);
		}
		if (abs(h[0] - h[n - 1]) > d * (n - 1)) {
			puts("impossible");
			continue;
		}
		for (int i = 0; i < n; i++)
			for (int j = -n; j <= n; j++)
				p.PB(h[i] + j * d);
		sort(p.begin(), p.end());
		p.resize(unique(p.begin(), p.end()) - p.begin());
		int m = p.size();

		vector<LL> best(m, inf);
		for (int j = 0; j < m; j++)
			if (p[j] == h[0])
				best[j] = 0;
		for (int i = 1; i < n; i++) {
			vector<LL> nxt(m, inf);
			int k = 0;
			for (int j = 0; j < m; j++) {
				for (; k < m && p[k] < p[j] - d; k++);
				for (; k + 1 < m && p[k + 1] <= p[j] + d && best[k+1] <= best[k]; k++);
					nxt[j] = min(nxt[j], best[k] + abs(p[j] - h[i]));
			}
			best = nxt;
		}
		
		for (int j = 0; j < m; j++)
			if (p[j] == h[n - 1]) {
				cout << best[j] << endl;
			}
	}
	return 0;
}

