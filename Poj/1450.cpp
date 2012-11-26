/*
 * Author: Yang Zhang
 * Created Time: Tue 11 Sep 2012 03:52:24 PM CST
 * File Name: 1450.cpp
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

int n, m;
int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Scenario #%d:\n", cas);
		scanf("%d%d", &n, &m);
		if (n % 2 == 0 || m % 2 == 0) {
			double ret = (double)m * n;
			printf("%.2f\n", ret);
		} else {
			double ret = (double)m * n - 1 + sqrt(2.0);
			printf("%.2f\n", ret);
		}
		puts("");
	}
	return 0;
}

