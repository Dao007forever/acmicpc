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

struct Edge {
	int v, next, vis;
}edge[11111];
int n;
string name[1111];
vector<string> ans;
int indeg[1111], outdeg[1111], vis[1111], f[1111];
int num, Head[1111];

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].vis = 0;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void dfs(int u, int id) {
	for (int i = Head[u]; i != -1; i = edge[i].next)
		if (!edge[i].vis) {
			edge[i].vis = 1;
			dfs(edge[i].v, i);
		}
	if (id != -1) ans.PB(name[id]);
}

int check() {
	int num = 0, t1 = 0, t2 = 0, id = -1;
	for (int i = 0; i < 26; i++) {
		if (vis[i]) {
			if (find(i) == i)
				num++;
			if (indeg[i] != outdeg[i]) {
				if (indeg[i] - outdeg[i] == 1)
					t1++;
				else if (outdeg[i] - indeg[i] == 1) {
					t2++;
					id = i;
				} else return -1;
			}
		}
	}
	if (num != 1) return -1;
	if (!((t1 == 1 && t2 == 1) || (t1 == 0 && t2 == 0)))
		return -1;
	if (id == -1) {
		for (int i = 0; i < 26; i++)
			if (outdeg[i] > 0) {
				id = i;
				break;
			}
	}
	return id;
}

bool cmp(string a, string b) {
	return a >= b;
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		ans.clear();
		num = 0;
		memset(Head, -1, sizeof(Head));
		memset(indeg, 0, sizeof(indeg));
		memset(outdeg, 0, sizeof(outdeg));
		memset(edge, 0, sizeof(edge));
		memset(vis, 0, sizeof(vis));
		scanf("%d", &n);
		for (int i = 0; i < 26; i++)
			f[i] = i;
		for (int i = 0; i < n; i++) {
			cin >> name[i];
		}
		sort(name, name + n, cmp);
		for (int i = 0; i < n; i++) {
			int u = name[i][0] - 'a', v = name[i][name[i].size() - 1] - 'a';
			vis[u] = vis[v] = 1;
			indeg[v]++; outdeg[u]++;
			addEdge(u, v);
			int x = find(u), y = find(v);
			if (x != y) f[x] = y;
		}

		int st = check();
		if (st != -1) {
			dfs(st, -1);
			reverse(ans.begin(), ans.end());
			for (int i = 0; i < ans.size(); i++)
				if (i == ans.size() - 1) cout << ans[i] << endl;
				else cout << ans[i] + '.';
		} else cout << "***" << endl;
	}
	return 0;
}
