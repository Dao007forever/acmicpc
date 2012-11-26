#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1005;
const int maxm = 100005;
struct DisJointSet{
	int rank[maxn], parent[maxn];

	DisJointSet() {
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
};
struct Edge {
	int u, v, vis;
	char type;
}e[maxm];
int n, m;
int vis[maxm];

void impossible() {
	cout << -1 << endl;
}

int main() {
	freopen("in.txt", "r", stdin);
	cin >> n >> m;
	if ((n - 1) & 1) {
		impossible();
		return 0;
	}
	
	DisJointSet elf;
	DisJointSet both;

	int santa = (n - 1) / 2;

	for (int i = 0; i < m; i++) {
		scanf("%d%d %c", &e[i].u, &e[i].v, &e[i].type);
		e[i].u--;
		e[i].v--;
		e[i].vis = 0;
	}

	for (int i = 0; i < m; i++) {
		if (e[i].type == 'S') {
			elf.Union(e[i].u, e[i].v);
		}
	}

	for (int i = 0; i < m; i++) {
		if (e[i].type == 'M' && elf.Find(e[i].u) != elf.Find(e[i].v)) {
			santa--;
			both.Union(e[i].u, e[i].v);
			elf.Union(e[i].u, e[i].v);
			e[i].vis = 1;
		}
	}

	for (int i = 0; i < m; i++) {
		if (e[i].type == 'M' && both.Find(e[i].u) != both.Find(e[i].v) && santa) {
			santa--;
			both.Union(e[i].u, e[i].v);
			e[i].vis = 1;
		}
	}

	int ee = (n - 1) / 2;
	for (int i = 0; i < m; i++) {
		if (e[i].type == 'S' && both.Find(e[i].u) != both.Find(e[i].v)) {
			both.Union(e[i].u, e[i].v);
			ee--;
			e[i].vis = 1;
		}
	}

	if (ee != 0 || santa != 0) {
		impossible();
		return 0;
	}

	cout << n - 1 << endl;
	int space = 0;
	for (int i = 0; i < m; i++)
		if (e[i].vis) {
			if (space) cout << " ";
			space = 1;
			cout << i + 1;
		}
	cout << endl;
	return 0;
}
