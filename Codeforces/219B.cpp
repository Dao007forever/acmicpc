/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 01:59:15 PM CST
 * File Name: 219B.cpp
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

unsigned long long p, d;
int main() {
	cin >> p >> d;
	unsigned long long x = p - d, ret;
	vector<LL> pow(20);
	pow[0] = 1ll;
	for (int i = 1; i <= 18; i++)
		pow[i] = pow[i - 1] * 10;
	int i = 1;
	do {
		ret = x;
		LL tmp = x / pow[i - 1] % 10;
		x = x - tmp * pow[i - 1] + 9 * pow[i - 1];
		i++;
	} while (x <= p);
	if (i >= 1) {
		i--;
		LL tmp = ret / pow[i - 1] % 10, rett = ret;
		for (int j = tmp + 1; j <= 9; j++) {
			LL num = rett - tmp * pow[i - 1] + j * pow[i - 1];
			if (num <= p && num > ret) ret = num;
		}
	}
	cout << ret << endl;
	return 0;
}

