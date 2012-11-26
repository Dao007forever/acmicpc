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

#define MAXN 60005
#define x first
#define y second
pair<double, pair<int, int> > p[MAXN];
int n;

LL dist(int x, int y) {
	return (LL)x * x + (LL)y * y;
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].y.x, &p[i].y.y);
		p[i].x = atan2(p[i].y.y, p[i].y.x);
	}

	sort(p, p + n);
	int k = n, n = 0;
	for (int i = 1; i < k; i++) {
		if (fabs(p[i].x - p[i - 1].x) <= 1e-7) {
			p[n].y.x += p[i].y.x;
			p[n].y.y += p[i].y.y;
		} else p[++n] = p[i];
	}
	++n;
	for (int i = 0; i < n; i++)
		p[n + i] = p[i];

	LL ret = 0;
	pair<int, int> sum = MP(0, 0);
	for (int i = 0, j = 0; i < n; i++) {
		for (; j - i < n && dist(sum.x + p[j].y.x, sum.y + p[j].y.y) >= dist(sum.x, sum.y); j++) {
			sum.x += p[j].y.x;
			sum.y += p[j].y.y;
		}
		ret = max(ret, dist(sum.x, sum.y));
		sum.x -= p[i].y.x;
		sum.y -= p[i].y.y;
	}
	cout << ret << endl;
	return 0;
}
