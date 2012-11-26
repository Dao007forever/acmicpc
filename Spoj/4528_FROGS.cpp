/*
 * Author: Yang Zhang
 * Created Time: Tue 11 Sep 2012 10:26:06 PM CST
 * File Name: 4528_FROGS.cpp
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
vector<pair<int, int> > compare;
int cnt[1 << 11];
bool check() {
	vector<int> key(n + 1);
	for (int i = 1; i <= n; i++)
		key[i] = (((1 << i) - 1) << (n - i));
	for (int i = 0; i < 1 << n; i++) {
		int mask = i;
		int tot = cnt[i & ((1 << 10) - 1)] + cnt[i >> 10];
		int res = key[tot];
		for (int j = 0; j < m && mask != res; j++)
			if (mask & (1 << compare[j].first) && !(mask & (1 << compare[j].second))) {
				mask ^= (1 << compare[j].first);
				mask ^= (1 << compare[j].second);
			}
		if (mask != res) return false;
	}
	return true;
}
int main() {
	for (int i = 0; i < 1 << 10; i++)
		for (int j = 0; j < 20; j++)
			cnt[i] += ((i & (1 << j)) > 0);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		compare.clear();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			compare.PB(MP(a, b));
			if (compare[i].first > compare[i].second)
				swap(compare[i].first, compare[i].second);
			compare[i].first--; compare[i].second--;
		}
		if (check()) puts("YES");
		else puts("NO");
	}
	return 0;
}

