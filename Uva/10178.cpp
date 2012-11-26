/*
 * 已知一个平面图的点和边，求有多少个面
 * 对于每个连通分量，用欧拉公式，然后再求和（其实不用统计每个连通分量的点数和边数，因为最终的和即为总点数和总边数，所以只需要统计连通分量数即可），也可以记录环的数量，面数=环数+1
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

#define maxn 222
int n, m;
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

int main() {
	while (cin >> n >> m) {
		char str[2][5];
		ufset.init();
		int ret = 1;
		for (int i = 0; i < m; i++) {
			scanf("%s %s", str[0], str[1]);
			int a = str[0][0] - 'A', b = str[1][0] - 'A';
			if (ufset.Find(a) != ufset.Find(b)) {
				ufset.Union(a, b);
			} else ret++;
		}
		cout << ret << endl;
	}
	return 0;
}
