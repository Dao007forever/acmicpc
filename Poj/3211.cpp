/*
 * Author: Yang Zhang
 * Created Time: Tue 18 Sep 2012 11:43:28 AM CST
 * File Name: 3211.cpp
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
	int m, n;
	while (cin >> m >> n) {
		if (m == 0 && n == 0) break;
		map<string, int> color;
		vector<int> p[m + 1];
		for (int i = 1; i <= m; i++) {
			string s;
			cin >> s;
			color[s] = i;
		}
		for (int i = 0; i < n; i++) {
			int t;
			string s;
			cin >> t >> s;
			p[color[s]].PB(t);
		}
		int ret = 0;
		for (int i = 1; i <= m; i++) {
			int sum = 0, Max = 0;
			vector<int>::iterator it;
			for (it = p[i].begin(); it != p[i].end(); it++)
				sum += *it;
			vector<bool> f(sum / 2 + 1);
			f[0] = true;
			for (it = p[i].begin(); it != p[i].end(); it++) {
				for (int i = sum / 2; i >= 0; i--)
					if (i - *it >= 0 && f[i - *it]) {
						f[i] = true;
						Max = max(Max, i);
					}
			}
			ret += sum - Max;
		}
		printf("%d\n", ret);
	}
	return 0;
}

