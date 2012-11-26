/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 08:55:32 PM UTC
 * File Name: main.cpp
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

int K;
int Euler(int n) {
	int ret = 1;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			n /= i;
			ret *= (i - 1);
			while (n % i == 0)
				n /= i, ret *= i;
		}
	}
	if (n > 1) ret *= n - 1;
	return ret;
}
int quickpow(LL a, int x, int mod) {
	LL ret = 1LL;
	for (; x; x >>= 1) {
		if (x & 1) ret = ret * a % mod;
		a = a * a % mod;
	}
	return (int)ret;
}
int main() {
	while (~scanf("%d", &K)) {
		int l1 = 0, l2 = 0, f2 = 0, f5 = 0;
		K *= 3;
		for (; K % 2 == 0; K /= 2) f2++;
		for (; K % 5 == 0; K /= 5) f5++;
		l2 = max(f2, f5);
		int phi = Euler(K);
		for (l1 = 1; l1 < phi; l1++)
			if (phi % l1 == 0) {
				int tmp = quickpow(10, l1, K);
				if (tmp == 1) break;
			}
		printf("%d %d %d\n", l1 + l2, l1, l2);
	}
	return 0;
}

