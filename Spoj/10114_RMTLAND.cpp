/*
 * Author: Yang Zhang
 * Created Time: Mon 27 Aug 2012 10:18:49 PM CST
 * File Name: 10114_RMTLAND.cpp
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

const int mod = 1000000007;
int prime[1000000], p;
bool vis[10000005];
int fac[10000001];
int n;

void getPrime() {
	p = 0;
	for (int i = 2; i <= 10000000; i++)
		if (!vis[i]) {
			for (int j = 2; i * j <= 10000000; j++)
				vis[i * j] = true;
			prime[p++] = i;
		}
}

int quickPow(int x, int b) {
	int ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = ((LL)ret * x) % mod;
		x = ((LL)x * x) % mod;
	}
	return ret;
}

int main() {
	fac[1] = 1;
	for (int i = 2; i <= 10000000; i++)
		fac[i] = ((LL)fac[i - 1] * i) % mod;
	getPrime();
	while (scanf("%d", &n) && n) {
		int div = 1;
		for (int i = 0; i < p && prime[i] <= n; i++) {
			int expo = 0;
			for (LL j = prime[i]; j <= n; j *= prime[i]) {
				expo += n / j;
			}
			if (expo & 1) div = ((LL)div * prime[i]) % mod;
		}
		div = quickPow(div, mod - 2);
		int ret = ((LL)fac[n] * div) % mod;
		printf("%d\n", ret);
	}
	return 0;
}

