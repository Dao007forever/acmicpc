/*
 * Author : Yang Zhang
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

struct node {
	vector<string> s;
}p[20];
int n;
int id[15];

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			string s;
			cin >> s;
			p[i].s.PB(s);
		}
		sort(p[i].s.begin(), p[i].s.end());
	}

	vector<string> ans;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bool flag = false;
		if (ans.size() > 0) {
			for (int j = 0; j < 3; j++)
				if (p[x].s[j] > ans[ans.size() - 1]) {
					ans.PB(p[x].s[j]);
					flag = true;
					break;
				}
		} else {
			flag = true;
			ans.PB(p[x].s[0]);
		}
		if (!flag) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}

	for (int i = 0; i < n; i++)
		cout << ans[i] << endl;
	return 0;
}
