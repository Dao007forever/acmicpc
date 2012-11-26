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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 30005
string name[MAXN];
map<string, int> id;
vector<string> son[MAXN];
int len[MAXN], last[MAXN], fa[MAXN];
int n, q;

void dfs(int u) {
	for (int i = 0; i < len[u]; i++)
		cout << ".";
	cout << name[u] << endl;
	if (son[u].size() == 0) return;
	sort(son[u].begin(), son[u].end());
	for (int i = 0; i < son[u].size(); i++)
		dfs(id[son[u][i]]);
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++) son[i].clear();
		id.clear();
		fa[0] = -1; len[0] = 0;
		cin >> name[0];
		id[name[0]] = 0;
		for (int i = 1; i < n; i++) {
			cin >> name[i];
			int j = 0;
			for (; name[i][0] == '.'; j++) {
				name[i].erase(name[i].begin());
			}
			len[i] = j;
			last[len[i]] = i;
			id[name[i]] = i;
			int pre = last[len[i] - 1];
			fa[i] = pre;
			son[pre].PB(name[i]);
		}

		scanf("%d", &q);
		while (q--) {
			string op;
			cin >> op;
			if (op[0] == 'L') {
				dfs(0);
			} else if (op[0] == 'b') {
				string s;
				cin >> s;
				int pre = fa[id[s]];
				if (pre == -1) printf("%d\n", 1);
				else printf("%d\n", son[pre].size());
			} else {
				string s1, s2;
				cin >> s1 >> s2;
				int a = id[s1], b = id[s2];
				if (len[a] < len[b]) swap(a, b);
				int pa = a, pb = b;
				for (; len[pa] > len[pb]; pa = fa[pa]);
				for (; pa != pb; pa = fa[pa], pb = fa[pb]);
				if (pa == a || pb == b) pa = fa[pa];
				cout << name[pa] << endl;
			}
		}
	}
	return 0;
}