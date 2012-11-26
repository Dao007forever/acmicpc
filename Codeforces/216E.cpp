/*
 * Author: Yang Zhang
 * Created Time: Sun 19 Aug 2012 03:38:49 PM UTC
 * File Name: 216E.cpp
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

int k, b, n, P;
int a[100005];
LL sum[100005];
map<int, int> mp;

int main() {
	cin >> k >> b >> n;
	P = k - 1;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum[i + 1] = (sum[i] + a[i]) % P;
	}
	LL ret = 0;
	for (int i = 0; i <= n; i++) {
		int pre = (sum[i] + P - b) % P;
		if (mp.find(pre) != mp.end()) {
			ret += (LL)mp[pre];
		}
		mp[sum[i]]++;
	}
	LL cnt = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0) {
			int ni;
			for (ni = i; ni < n && a[ni] == 0; ni++);
			cnt += (LL)(ni - i) * (ni - i + 1) / 2;
			i = ni;
		}
	}
	if (b == 0) {
		ret = cnt;
	} else if (b == P) {
		ret -= cnt;
	}
	cout << ret << endl;
}

