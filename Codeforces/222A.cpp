/*
 * Author: Yang Zhang
 * Created Time: Thu 13 Sep 2012 01:51:04 PM CST
 * File Name: 222A.cpp
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
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	bool flag = true;
	for (int i = k; i < n; i++)
		if (a[i] != a[k - 1]) {
			flag = false;
			break;
		}
	if (flag) {
		int ret = -1;
		for (int i = k - 1; i >= 0; i--) {
			if (a[i] != a[k - 1]) {
				ret = i;
				break;
			}
		}
		printf("%d\n", ret + 1);
	} else puts("-1");
}

