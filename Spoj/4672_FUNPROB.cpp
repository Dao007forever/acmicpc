/*
 * Author: Yang Zhang
 * Created Time: Sun 09 Sep 2012 10:11:27 PM CST
 * File Name: 4672_FUNPROB.cpp
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

LL n, m;
int main() {
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		if (n > m) {
			puts("0.000000");
		} else {
			double ret = 1;
			ret -= (double)n/(m+1);
			printf("%.6f\n", ret);
		}
	}
	return 0;
}

