/*
 * Author: Yang Zhang
 * Created Time: Fri 29 Jun 2012 07:51:34 PM UTC
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

int n;
LL ret;
vector<int> p;

void init() {
	p.clear();
	int k = n;
	for (int i = 2; i * i <= k; i++) 
		if (k % i == 0) {
			p.push_back(i);
			while (k % i == 0) k /= i;
		}
	if (k > 1) p.push_back(k);
}

void Search(int cur, LL v) {
	if (v >= ret || v >= 2000000) return;
	if (cur >= p.size()) {
		if (v > n) ret = v;
		return;
	}
	v *= p[cur];
	Search(cur + 1, v);
	while (v <= n) {
		v *= p[cur];
		Search(cur + 1, v);
	}
}

int main() {
	while (~scanf("%d", &n)) {
		if (n == 1) {
			cout << "Not Exist!" << endl;
			continue;
		}

		init();
		ret = 1LL << 60;
		Search(0, 1);
		if (ret >= 2000000)	cout << "Not Exist!" << endl;
		else cout << ret << endl;
	}
	return 0;
}

