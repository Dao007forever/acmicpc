/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 06:42:20 PM UTC
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

LL a, b;

void work() {
	printf("%lld %lld\n", a, b);
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%lld%lld", &a, &b);
		if (b % a == 0) {
			work();
		} else {
			puts("-1");
		}
	}
	return 0;
}

