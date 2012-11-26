/*
 * Author: Yang Zhang
 * Created Time: Sun 03 Jun 2012 11:54:49 PM UTC
 * File Name: A.cpp
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

char str[55][55];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", str[i] + 1);
	int ret = 100000;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == '#') {
				cnt++;
				int tot = 0;
				if (str[i + 1][j] == '#')
					tot++;
				if (str[i][j + 1] == '#')
					tot++;
				if (str[i - 1][j] == '#')
					tot++;
				if (str[i][j - 1] == '#')
					tot++;
				ret = min(ret, tot);
			}
		}
	if (cnt == 1 || cnt == 2) printf("-1");
	else printf("%d\n", ret);
	return 0;
}

