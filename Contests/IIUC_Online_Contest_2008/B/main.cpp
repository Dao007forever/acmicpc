/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 06:24:57 PM UTC
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

int n;
int cnt[111];

void work() {
	printf("%d\n", 3 * n / 2);
	for (int i = 1; i <= n; i++)
		cnt[i] = 3;
	while (true) {
		for (int i = 1; i <= n; i++)
			if (cnt[i]) {
				for (int j = i + 1; j <= n; j++)
					if (cnt[j]) {
						printf("%d %d\n", i, j);
						cnt[i]--;
						cnt[j]--;
						if (cnt[i] == 0) break;
					}
			}
		bool flag = false;
		for (int i = 1; i <= n; i++)
			if (cnt[i]) {
				flag = true;
				break;
			}
		if (!flag) break;
	}
}

int main() {
	while (scanf("%d", &n) && n) {
		if (n & 1 || n <= 3) puts("Impossible");
		else {
			work();
		}
	}
	return 0;
}

