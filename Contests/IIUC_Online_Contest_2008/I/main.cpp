/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 08:07:22 PM UTC
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

int main() {
	int n;
	while (scanf("%d", &n) && n) {
		n = n * (n - 1) / 2;
		if (n > 1 && n % 3 == 0) puts("YES");
		else puts("NO");
	}
	return 0;
}

