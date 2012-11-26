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
string s[111];
map<string, int> mp;

int main() {
	cin >> n;
	int cnt = 0;
	bool flag = true;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		if (mp[s[i]] == 0) mp[s[i]] = ++cnt;
		else flag = false;
	}
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	if (n == 2) {
		if (!flag) cout << 0 << endl;
		else {
			cout << 1 << endl;
			cout << s[0] << "-" << s[1] << endl;
		}
		return 0;
	}
	if (!flag) {
		cout << "Impossible" << endl;
	} else {
		cout << n << endl;
		for (map<string, int>::iterator it = mp.begin(); it != mp.end(); it++)
			cout << it->first << "-" << "zjsxzy" << endl;
	}
	return 0;
}
