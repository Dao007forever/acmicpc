/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 12:38:01 PM UTC
 * File Name: D.cpp
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

int n;
int main() {
	cin >> n;
	vector<vector<int> > p(n);
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		while (k--) {
			int pos;
			cin >> pos;
			p[i].PB(pos);
		}
		sort(p[i].begin(), p[i].end());
	}
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int pre = (i - 1 + n) % n, nxt = (i + 1) % n;
		for (int j = 1; j < p[i].size(); j++) {
			int l = p[i][j - 1], r = p[i][j];
			int num_pre = lower_bound(p[pre].begin(), p[pre].end(), r) - lower_bound(p[pre].begin(), p[pre].end(), l);
			int num_nxt = lower_bound(p[nxt].begin(), p[nxt].end(), r) - lower_bound(p[nxt].begin(), p[nxt].end(), l);
			if (num_pre != num_nxt) ret++;
		}
	}
	cout << ret << endl;
	return 0;
}

