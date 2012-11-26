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

const int maxn = 100005;
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init() {
		for (int i = 0; i < maxn; i++) {
			rank[i] = 1;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		parent[x] = y;
		rank[y] += rank[x];
	}
}ufset;

int main() {
	freopen("in", "r", stdin);
	int Test, n;
	cin >> Test;
	while (Test--) {
		cin >> n;
		ufset.init();
		map<string, int> mp;
		int tot = 0;
		while (n--) {
			string s1, s2;
			cin >> s1 >> s2;
			int t1 = mp[s1], t2 = mp[s2];
			if (t1 == 0) {
				mp[s1] = ++tot;
			}
			if (t2 == 0) {
				mp[s2] = ++tot;
			}
			int f1 = ufset.Find(mp[s1]), f2 = ufset.Find(mp[s2]);
			if (f1 != f2) {
				cout << ufset.rank[f1] + ufset.rank[f2] << endl;
				ufset.Union(mp[s1], mp[s2]);
			} else {
				cout << ufset.rank[f1] << endl;
			}
		}
	}
	return 0;
}
