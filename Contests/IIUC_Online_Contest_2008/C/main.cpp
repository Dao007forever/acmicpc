/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 05:47:34 PM UTC
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
LL a[5555];
int last[5555];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
		}
		sort(a, a + n);
		for (int i = n - 1; i >= 1; i--) {
			if (i + 1 < n && a[i] == a[i + 1])
				last[i] = last[i + 1];
			else last[i] = i;
		}
		LL ret = 0;
		for (int i = 0; i < n; i++) {
			int k = i;
			for (int j = i + 1; j < n; j++) {
				while (k < n && a[i] + a[j] > a[k])
					k++;
				if (a[k] == a[i] + a[j]) {
					ret += last[k] - k + 1;
				}
			}
		}
		cout << ret << endl;
	}
	return 0;
}

