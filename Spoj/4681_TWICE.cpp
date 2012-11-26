#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, ret;
string s;
map<string, int> mp;

bool check(int len) {
	//mp.clear();
	for (int i = 0; i + len - 1 < n; i++) {
		string sub = s.substr(i, len);
		mp[sub]++;
		if (mp[sub] == 2) {
			ret = len;
			return true;
		}
	}
	return false;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	cin >> s;
	int l = 0, r = n + 1;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%d\n", ret);
	return 0;
}
