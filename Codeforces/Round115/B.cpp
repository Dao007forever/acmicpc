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

int n;
map<string, int> mp;
int v[1111];
string name[1111], ans[1111];

string calc(int num) {
	int u = mp.size();
	if (num * 2 > u) return "noob";
	if (num * 5 > u) return "random";
	if (num * 10 > u) return "average";
	if (num * 100 > u) return "hardcore";
	return "pro";
}

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int s;
		cin >> name[i] >> s;
		if (mp.find(name[i]) == mp.end()) {
			mp[name[i]] = s;
			v[i] = 1;
		}
		else mp[name[i]] = max(mp[name[i]], s);
	}

	for (int i = 0; i < n; i++) 
	if (v[i]) {
		int cnt = 0;
		for (int j = 0; j < n; j++)
			if (v[j] && mp[name[j]] > mp[name[i]]) cnt++;
		ans[i] = calc(cnt);
	}

	cout << mp.size() << endl;
	for (int i = 0; i < n; i++)
		if (v[i]) {
			cout << name[i] << " " << ans[i] << endl;
		}
	return 0;
}
