/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 09:03:31 PM UTC
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

char str[20];
int a[20];
int n;
vector<int> v;
LL dp[17][17][5], comb[20][20];

int change(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	else return c - 'A' + 10;
}

void init() {
	for (int i = 0; i <= 16; i++)
		comb[i][0] = 1;
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= i; j++)
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
}

void work() {
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for (int i = 1; i <= v.size(); i++) {
		int num = v[i - 1];
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < 5; k++) 
				if (dp[i - 1][j][k] > 0) {
					for (int t = 0; t <= a[num]; t++) {
						dp[i][j + t][(k + t * num) % 5] += dp[i - 1][j][k] * comb[j + t][t];
					}
				}
			}
		}
	LL ret = 0;
	for (int j = 1; j <= n; j++)
		ret += dp[v.size()][j][0];
	printf("%lld\n", ret);
}

int main() {
	init();
	while (scanf("%s", str)) {
		if (!strcmp(str, "#")) break;
		v.clear();
		memset(a, 0, sizeof(a));
		n = strlen(str);
		for (int i = 0; i < n; i++) {
			int tmp = change(str[i]);
			a[tmp]++;
			v.push_back(tmp);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		work();
	}
	return 0;
}

