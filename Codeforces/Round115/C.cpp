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

int n, t;
struct Monster {
	LL k, c;
}T[111];
LL p[111];

bool cmp(Monster a, Monster b) {
	return a.c < b.c;
}

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> T[i].k >> T[i].c;
	}
	sort(T, T + n, cmp);
	
	cin >> t;
	for (int i = 0; i < t; i++)
		cin >> p[i];
	LL f = 1;
	int k = 0;
	LL ret = 0;
	for (int i = 0; i < t; i++, f++) {
		LL cnt;
		if (i) cnt = p[i] - p[i - 1];
		else cnt = p[i];
		for (; k < n && cnt; ) {
			if (T[k].k >= cnt) {
				ret += T[k].c * cnt * f;
				T[k].k -= cnt;
				cnt = 0;
				if (T[k].k == 0) k++;
			} else {
				ret += T[k].c * T[k].k * f;
				cnt -= T[k].k;
				T[k].k = 0;
				k++;
			}
		}
		if (k == n) break;
	}
	if (k < n) {
		for (; k < n; k++)
			ret += T[k].k * T[k].c * f;
	}
	cout << ret << endl;
	return 0;
}
