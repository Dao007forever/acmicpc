/*
 * Author: Yang Zhang
 * Created Time: Fri 31 Aug 2012 11:34:36 PM CST
 * File Name: A.cpp
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

#define fi first
#define se second
int n;
int a[200005];
int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int cnt = 0;
	vector<pair<int, int> > p;
	for (int i = 1; i < n; i++)
		if (a[i] < a[i - 1]) {
			p.PB(MP(i - 1, i));
			cnt++;
		}
	if (cnt == 0) {
		puts("YES");
		return 0;
	}
	if (cnt > 2) {
		puts("NO");
		return 0;
	}
	if (cnt == 1) {
		int x1 = p[0].fi, x2 = p[0].se;
		for (; x1 - 1 >= 0 && a[x1 - 1] == a[x1]; x1--);
		for (; x2 + 1 < n && a[x2 + 1] == a[x2]; x2++);
		swap(a[x1], a[x2]);
		bool flag = true;
		for (int i = 1; i < n; i++)
			if (a[i] < a[i - 1]) {
				flag = false;
				break;
			}
		if (flag) puts("YES");
		else puts("NO");
		return 0;
	}
	if (cnt == 2) {
		int x1 = p[0].fi, x2 = p[1].se;
		for (; x1 - 1 >= 0 && a[x1 - 1] == a[x1]; x1--);
		for (; x2 + 1 < n && a[x2 + 1] == a[x2]; x2++);
		swap(a[x1], a[x2]);
		bool flag = true;
		for (int i = 1; i < n; i++)
			if (a[i] < a[i - 1]) {
				flag = false;
				break;
			}
		if (flag) puts("YES");
		else puts("NO");
		return 0;

	}
	return 0;
}

