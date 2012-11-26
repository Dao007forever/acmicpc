/*
 * Author: Yang Zhang
 * Created Time: Sun 19 Aug 2012 02:15:53 PM UTC
 * File Name: 9858.cpp
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

const LL P = 500000003;
int n;
int x, y;
int u, d, l, r;
LL facN, invf[1000005], inv[1000005];
void init() {
	facN = 1;
	for (int i = 1; i <= n; i++) {
		facN = (facN * i) % P;
	}
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		inv[i] = (-inv[P % i] * (P / i) % P + P) % P;
	}
	invf[0] = invf[1] = 1;
	for (int i = 2; i <= n; i++) {
		invf[i] = (invf[i - 1] * inv[i]) % P;
	}
}
int main() {
	scanf("%d%d%d", &n, &x, &y);
	init();
	LL ret = 0;
	for (u = 0; u <= n; u++) {
		d = u - y;
		int a = x, b = n - d - u;
		if ((a & 1) != (b & 1)) continue;
		r = (a + b) / 2; l = (b - a) / 2;
		if (u >= 0 && d >= 0 && r >= 0 && l >= 0) {
			LL tmp = (facN * invf[u]) % P;
			tmp = (tmp * invf[d]) % P;
			tmp = (tmp * invf[l]) % P;
			tmp = (tmp * invf[r]) % P;
			ret = (ret + tmp) % P;
		}
	}
	cout << ret << endl;
	return 0;
}

