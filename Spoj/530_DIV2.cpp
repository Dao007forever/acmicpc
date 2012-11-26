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

const int maxn = 1000000;
int f[maxn + 5];
int d[maxn + 5];

int main() {
	for (int i = 1; i <= maxn; i++)
		for (int j = i; j <= maxn; j += i)
			d[j]++;
	for (int i = 1; i <= maxn; i++)
		if (d[i] > 3) f[i] = 1;
	for (int i = 1; i <= maxn; i++)
		for (int j = i; j <= maxn; j += i)
			if (f[j] && d[j] % d[i] != 0)
				f[j] = 0;
	int ret = 0;
	for (int i = 1; i <= maxn; i++)
		if (f[i]) {
			ret++;
			if (ret % 108 == 0) printf("%d\n", i);
		}
}
