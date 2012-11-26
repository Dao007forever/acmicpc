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

#define maxn 1005
list<int> path;
int n;
bool g[maxn][maxn];
vector<vector<int> > ans;

void record() {
	if (path.size() <= 2) return; 
	vector<int> t;
	bool flag = false;
	for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
		if (*it == 1) flag = true;
		if (flag) t.PB(*it);
	}
	for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
		t.PB(*it);
		if (*it == 1) break;
	}
	ans.PB(t);
}

void output() {
	for (int i = 0; i < ans.size(); i++) {
		for (int j = 0; j < ans[i].size(); j++)
			printf("%d%c", ans[i][j], j == ans[i].size() - 1 ? '\n' : ' ');
	}
}

bool hamilton(int start) {
	path.clear();
	ans.clear();
	path.PB(start);
	list<int>::iterator cur, pre;
	for (int i = 1; i <= n; i++) {
		if (i == start) continue;
		cur = path.begin();
		if (g[i][*cur]) {
			path.push_front(i);
			record();
			continue;
		}
		cur = path.end(); cur--;
		if (g[*cur][i]) {
			path.PB(i);
			record();
			continue;
		}

		pre = cur = path.begin();
		cur++;
		for (; cur != path.end(); cur++, pre++) {
			if (g[*pre][i] && g[i][*cur]) {
				path.insert(cur, i);
				break;
			}
		}
		record();

		pre = path.begin(); cur = path.end(); cur--;
		if (!g[*cur][*pre]) return false;
	}
	pre = path.begin(); cur = path.end(); cur--;
	if (g[*cur][*pre]) return true;
	return false;
}

char input[maxn];
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%s", input + 1);
			for (int j = 1; j <= n; j++) {
				g[i][j] = input[j] == '1';
			}
		}
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (hamilton(i)) {
				flag = true;
				break;
			}
		}
		if (!flag) puts("impossible");
		else output();
	}
	return 0;
}