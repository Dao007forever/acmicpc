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
const int maxn = 1111;
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init() {
		for (int i = 0; i < maxn; i++) {
			rank[i] = 0;
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
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}
}ufset;

int n;
vector<pair<int, int> > v;
vector<int> ans;

int main() {
	ufset.init();
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		if (ufset.Find(a) != ufset.Find(b)) {
			ufset.Union(a, b);
		} else {
			v.PB(MP(a, b));
		}
	}
	for (int i = 1; i <= n; i++)
		if (ufset.parent[i] == i) ans.push_back(i);
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++)
		printf("%d %d %d %d\n", v[i].first, v[i].second, ans[i], ans[i + 1]);
	return 0;
}
