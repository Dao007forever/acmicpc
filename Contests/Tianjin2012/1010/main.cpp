/*
 * Author: Yang Zhang
 * Created Time: Sun 09 Sep 2012 12:11:58 PM CST
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

int n, m;
int a[5555];
map<int, int> mp;
set<int> st;
int num[5555];

int main() {
	num['a'] = num['b'] = num['c'] = 2;
	num['d'] = num['e'] = num['f'] = 3;
	num['g'] = num['h'] = num['i'] = 4;
	num['j'] = num['k'] = num['l'] = 5;
	num['m'] = num['n'] = num['o'] = 6;
	num['p'] = num['q'] = num['r'] = num['s'] = 7;
	num['t'] = num['u'] = num['v'] = 8;
	num['w'] = num['x'] = num['y'] = num['z'] = 9;
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		mp.clear(); st.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d\n", &a[i]);
			st.insert(a[i]);
		}
		for (int i = 0; i < m; i++) {
			string s;
			cin >> s;
			int x = 0;
			for (int i = 0; i < s.size(); i++)
				x = x * 10 + num[s[i]];
			if (st.find(x) != st.end()) {
				mp[x]++;
			}
		}
		for (int i = 0; i < n; i++) {
			printf("%d\n", mp[a[i]]);
		}
	}
	return 0;
}

