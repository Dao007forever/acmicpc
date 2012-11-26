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

int n, s;
int dp[2][15010][2];
int h[2][15010][2];

int main() {
	cin >> n >> s;
	int n1 = s - 2 * n;
	int n0 = n - n1;
	if (n == 1) {
		printf("%.7f\n", n0 ? 1.00 : 0.00);
		return 0;
	}
	double ret = (double)n0 / n + (double)n1 * n0 / n * 2.0;
	printf("%.7f\n", ret);
	return 0;
}
