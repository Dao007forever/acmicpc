/*
 * Author: Yang Zhang
 * Created Time: Wed 12 Sep 2012 09:36:46 PM CST
 * File Name: 3409.cpp
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

void init(string &x) {
	if (x.size() == 1) return;
	int i = 0;
	for (; i < x.size() && x[i] == '0'; i++);
	if (i == x.size()) x.erase(0, i - 1);
	else x.erase(0, i);
}

int main() {
	int n;
	while (~scanf("%d", &n)) {
		map<pair<string, string>, int> mp;
		vector<int> deg(2*n);
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			string x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			init(x1); init(y1); init(x2); init(y2);
			pair<string, string> p1 = MP(x1, y1), p2 = MP(x2, y2);
			if (mp.find(p1) == mp.end()) mp[p1] = cnt++;
			if (mp.find(p2) == mp.end()) mp[p2] = cnt++;
			deg[mp[p1]]++; deg[mp[p2]]++;
		}
		bool flag = true;
		for (int i = 0; i < cnt; i++)
			if (deg[i] & 1) {
				flag = false;
				break;
			}
		if (flag) puts("1");
		else puts("0");
	}
	return 0;
}

