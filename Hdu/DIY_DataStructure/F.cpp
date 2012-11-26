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

#define MAXN 80005
int f[MAXN], h[MAXN];
int n;

int main() {
	freopen("F.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &h[i]);
		memset(f, 0, sizeof(f));
		LL ret = 0;
		for (int i = n; i >= 1; i--) {
			f[i] = i + 1;
			int cnt = 0;
			while (f[i] <= n && h[i] > h[f[i]]) {
				cnt += f[f[i]] - f[i];
				f[i] = f[f[i]];
			}
			ret += cnt;
		}
		cout << ret << endl;
	}
	return 0;
}
