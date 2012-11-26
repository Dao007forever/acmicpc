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

#define maxn 100005
typedef long long LL;
int n, m;
LL mod;
int cnt[maxn];
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i < n; i++) {
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

int main() {
	cin >> n >> m >> mod;
	ufset.init(n);
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		if (ufset.Find(a) != ufset.Find(b)) {
			ufset.Union(a, b);
		}
	}
	for (int i = 0; i < n; i++)
		cnt[ufset.Find(i)]++;
	LL ret = 1 % mod;
	int k = 0;
	for (int i = 0; i < n; i++)
		if (ufset.Find(i) == i) {
			ret = (ret * cnt[i]) % mod;
			k++;
		}
	if (k == 1) {
		cout << 1LL % mod << endl;
		return 0;
	}
	for (int i = 0; i < k - 2; i++) {
		ret = (ret * n) % mod;
	}
	cout << ret << endl;
	return 0;
}

