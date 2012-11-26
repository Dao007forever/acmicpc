/*
 * Author: Yang Zhang
 * Created Time: Thu 30 Aug 2012 01:35:10 PM CST
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
vector<int> p[115];

bool check(int s) {
	for (int i = 0; i < m; i++) {
		int cnt = 0;
		for (int j = 0; j < p[i].size(); j++)
			if (s & (1 << p[i][j])) cnt++;
		if (cnt == 0 || cnt == p[i].size()) return false;
	}
	return true;
}

int main() {
	int Test;
	cin >> Test;
	string ans;
	while (Test--) {
		cin >> n >> m;
		string input;
		getline(cin, input);
		for (int i = 0; i < m; i++) {
			p[i].clear();
			istringstream iss;
			getline(cin, input);
			iss.str(input);
			int x;
			while (iss >> x) {
				x--;
				p[i].PB(x);
			}
		}
		bool flag = false;
		for (int i = 1; i < (1 << n); i++) {
			if (check(i)) {
				//printf("%d\n", i);
				flag = true;
				break;
			}
		}
		if (flag) {
			ans += 'Y';
		} else {
			ans += 'N';
		}
	}
	cout << ans;
	return 0;
}
