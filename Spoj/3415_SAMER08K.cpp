/*
 * Author: Yang Zhang
 * Created Time: Sat 15 Sep 2012 09:20:52 PM CST
 * File Name: 3415_SAMER08K.cpp
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

#define MAXN 20005
int n, sum;
int a[MAXN], s[MAXN];

bool check(int x) {
	vector<int> nxt(2*n+5, -1);
	int l = 1, r = 1;
	for (; l <= 2*n; l++) {
		for (; s[r] - s[l - 1] < x && r <= 2*n; r++);
		if (r <= 2*n && s[r] - s[l - 1] == x) nxt[l] = r;
	}
	vector<bool> vis(2*n+5, false);
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		int j = i;
		for (; j < n + i; j = nxt[j] + 1) {
			if (nxt[j] == -1) break;
			vis[j] = true;
		}
		if (j == n + i) return true;
	}
	return false;
}

int work() {
	int i;
	for (i = 1; i * i <= sum; i++) {
		if (sum % i != 0) continue;
		if (sum / i <= 2) continue;
		if (sum / i <= n && check(i)) {
			return sum / i;
		}
	}
	for (; i >= 3; i--) {
		if (sum % i != 0) continue;
		if (i <= n && check(sum / i)) {
			return i;
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d", &n) && n) {
		s[0] = 0; sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum += a[i];
			a[n + i] = a[i];
		}
		for (int i = 1; i <= 2*n; i++) {
			s[i] = s[i - 1] + a[i];
		}
		int ret = work();
		if (ret != -1) ret = n - ret;
		printf("%d\n", ret);
	}
	return 0;
}

