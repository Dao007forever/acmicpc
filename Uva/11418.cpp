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
int mk[33], cx[33], cy[33];
int adj[33][33];
vector<string> name[33];

int path(int u) {
	for (int i = 1; i <= n; i++)
		if (adj[u][i] &&!mk[i]) {
			mk[i] = 1;
			if (!cy[i] || path(cy[i])) {
				cx[u] = i;
				cy[i] = u;
				return 1;
			}
		}
	return 0;
}

int maxMatch() {
	int ret = 0;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));
	for (int i = 1; i <= n; i++)
		if (!cx[i]) {
			memset(mk, 0, sizeof(mk));
			ret += path(i);
		}
	return ret;
}

void output() {
	for (int i = 0; i < n; i++) {
		char ch = (char)(i + 'A');
		int id = cy[i + 1] - 1;
		for (int j = 0; j < name[id].size(); j++)
			if (name[id][j][0] == ch) {
				cout << name[id][j] << endl;
				break;
			}
	}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d:\n", cas);
		memset(adj, 0, sizeof(adj));
		cin >> n;
		for (int i = 0; i <= n; i++)
			name[i].clear();
		for (int i = 0; i < n; i++) {
			int k;
			cin >> k;
			while (k--) {
				string s;
				cin >> s;
				s[0] = toupper(s[0]);
				for (int j = 1; j < s.size(); j++)
					s[j] = tolower(s[j]);
				name[i].push_back(s);
				adj[i + 1][s[0] - 'A' + 1] = 1;
			}
		}
		int ret = maxMatch();
		output();
	}
	return 0;
}
