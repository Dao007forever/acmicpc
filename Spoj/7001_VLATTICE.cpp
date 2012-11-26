/*
 * Author: Yang Zhang
 * Created Time: Tue 11 Sep 2012 03:05:20 PM CST
 * File Name: 7001_VLATTICE.cpp
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

#define MAXN 1000000
LL ans[MAXN + 5], fi[MAXN + 5];
bool mark[MAXN + 5];
vector<int> prime[MAXN + 5];

inline LL sqr(int x) {
	return (LL)x * x;
}

LL calc(int n) {
	int sz = prime[n].size();
	LL ret = 0;
	for (int i = 1; i < (1 << sz); i++) {
		int cnt = 0, mul = 1;
		for (int j = 0; j < sz; j++)
			if (i & (1 << j)) {
				cnt++; mul *= prime[n][j];
			}
		if (cnt & 1) ret += sqr(n / mul);
		else ret -= sqr(n / mul);
	}
	return ret;
}

int main() {
	for (int i = 2; i <= MAXN; i++)
		fi[i] = i;
	for (int i = 2; i <= MAXN; i++)
		if (!mark[i]) {
			fi[i] = i - 1;
			prime[i].PB(i);
			for (int j = 2; i * j <= MAXN; j++) {
				mark[i * j] = true;
				prime[i * j].PB(i);
				fi[i * j] = fi[i * j] * (i - 1) / i;
			}
		}
	ans[1] = 7;
	for (int i = 2; i <= MAXN; i++) {
		ans[i] = ans[i - 1];
		ans[i] += 3 * fi[i];
		LL tmp = sqr(i) - calc(i);
		ans[i] += tmp * 3;
	}

	int Test, n;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		printf("%lld\n", ans[n]);
	}
	return 0;
}

