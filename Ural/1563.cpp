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

int n;
map<string, int> mp;

int main() {
	freopen("in", "r", stdin);
	int ret = 0, t = 0;
	cin >> n;
	string tmp;
	getline(cin, tmp);
	for (int i = 1; i <= n; i++) {
		string s;
		getline(cin, s);
		if (mp.find(s) == mp.end()) {
			mp[s] = ++t;
		} else {
			ret++;
		}
	}
	cout << ret << endl;
	return 0;
}
