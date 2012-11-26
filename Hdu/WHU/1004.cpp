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

#define MAXN 100005
int	N;
struct node {
	int c, d;
}p[MAXN];

bool cmp(node a, node b) {
	return a.d < b.d;
}

bool check(LL lim) {
	LL t = 0, ret = 0;
	for (int i = 0; i < N; i++) {
		t += (long long)p[i].c;
		ret = max(ret, t - p[i].d);
	}
	return ret <= lim;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		scanf("%d", &N);
		LL l = 0, r = 0;
		for (int i = 0; i < N; i++) {
			//cin >> p[i].c >> p[i].d;
			scanf("%d%d", &p[i].c, &p[i].d);
			r += (long long)p[i].c;
		}
		sort(p, p + N, cmp);

		LL ret;
		while (l <= r) {
			LL mid = (l + r) >> 1;
			if (check(mid)) {
				ret = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		cout << ret << endl;
	}
	return 0;
}
