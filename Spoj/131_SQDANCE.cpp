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

#define maxn 100005
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i <= n; i++) {
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
	int Test;
	cin >> Test;
	while (Test--) {
		int n, m;
		cin >> n >> m;
		ufset.init(n);
		int ret = 0;
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			if (ufset.Find(a) != ufset.Find(b))
				ufset.Union(a, b);
			else ret++;
		}
		cout << ret << endl;
	}
	return 0;
}
