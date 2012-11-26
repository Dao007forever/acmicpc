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

#define MAXN 1000005
int n;
int a[MAXN];

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);

		LL ret = a[0];
		int k = n - 1;
		while (true) {
			for (; k > 0; k--) {
				if (a[k] < 0)
					ret += (long long)a[k] * 2;
				else break;
			}
			if (k == 0) break;

			LL tmp = 0;
			for (; k >= 0; k--) {
				tmp += a[k];
				ret += tmp;
				if (tmp < 0 || k == 0) {
					if (k != 0 && a[k] < 0) {
						ret += tmp;
						ret -= a[k];
					}
					ret -= a[k];
					break;
				}
			}
		}
		cout << ret << endl;
	}
	return 0;
}
