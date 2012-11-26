/*
 * Author: Yang Zhang
 * Created Time: Sat 08 Sep 2012 07:15:00 PM CST
 * File Name: 4272.cpp
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
bool check(const vector<int> &x) {
	if (x.size() & 1) return false;
	map<int, int> mp;
	for (int i = 0; i < x.size(); i++)
		mp[x[i]]++;
	for (int i = 0; i < x.size(); i++)
		if (mp[x[i]] & 1) return false;
	return true;
}
int main() {
	while (~scanf("%d", &n)) {
		vector<int> a(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		if (n & 1) {
			puts("0");
			continue;
		}
		reverse(a.begin(), a.end());
		if (n <= 6) {
			if (check(a)) {
				puts("1");
			} else {
				puts("0");
			}
		} else {
			vector<int> st;
			for (int i = 0; i < 6; i++)
				st.PB(a[i]);
			queue<int> ed;
			queue<vector<int> > q;
			q.push(st);
			ed.push(6);
			bool flag = false;
			while (!ed.empty()) {
				int u = ed.front(); ed.pop();
				vector<int> cur = q.front(); q.pop();
				if (u == n) {
					if (check(cur)) {
						flag = true;
						break;
					}
					continue;
				}
				for (int i = 1; i < cur.size(); i++) {
					if (cur[0] == cur[i]) {
						vector<int> tmp = cur;
						tmp.erase(tmp.begin() + i);
						tmp.erase(tmp.begin());
						tmp.PB(a[u]); tmp.PB(a[u+1]);
						ed.push(u+2);
						q.push(tmp);
					}
				}
			}
			if (flag) puts("1");
			else puts("0");
		}
	}
	return 0;
}

