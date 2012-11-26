/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 05:47:35 PM UTC
 * File Name: 217B.cpp
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

const int inf = 1000000000;
int n, r, ret, mlen;
char ans[1000005], t[1000005];

void solve(int x, int y) {
	int len = 0;
	for (; x != y; ) {
		if (x < y) {
			y = y - x;
			t[len++] = 'B';
		} else {
			x = x - y;
			t[len++] = 'T';
		}
	}
	if (x > 1) return;
	t[len++] = 'T';
	if (len != n) return;
	int cnt = 0;
	for (int i = 1; i < len; i++)
		if (t[i] == t[i - 1]) cnt++;
	if (cnt < ret) {
		ret = cnt;
		for (int i = 0; i < len; i++)
			ans[i] = t[i];
	}
}
int main() {
	cin >> n >> r;
	ret = inf;
	for (int i = 1; i <= r; i++) {
		solve(i, r);
		solve(r, i);
//		printf("%d\n", i);
	}
	if (ret == inf) {
		puts("IMPOSSIBLE");
		return 0;
	}
	printf("%d\n", ret);
	for (int i = n - 1; i >= 0; i--)
		printf("%c", ans[i]);
	return 0;
}

