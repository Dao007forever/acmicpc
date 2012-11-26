/*
 * Author: Yang Zhang
 * Created Time: Fri 29 Jun 2012 09:49:58 PM UTC
 * File Name: main.cpp
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

bool pick[33], ans[33];
bool adj[33][33];
int n, m, ret;
void Search(int cur, int now) {
	if (now >= ret) return;
	if (cur >= n) {
		memcpy(ans, pick, sizeof(ans));
		ret = now;
		return;
	}

	bool flag = true;
	for (int i = 0; i < cur; i++) {
		if (!pick[i] && adj[i][cur]) {
			flag = false;
			break;
		}
	}
	
	if (flag) Search(cur + 1, now);//not selected

	pick[cur] = 1;
	Search(cur + 1, now + 1);//selected
	pick[cur] = 0;
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d: ", cas);

		memset(adj, 0, sizeof(adj));
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u][v] = adj[v][u] = true;
		}

		ret = 1 << 30;
		memset(ans, 0, sizeof(ans));
		memset(pick, 0, sizeof(pick));
		Search(0, 0);

		vector<int> p;
		printf("%d\n", ret);
		if (ret == 0) {
			puts("");
			continue;
		}
		for (int i = 0; i < n; i++)
			if (ans[i]) {
				p.PB(i);
			}
		for (int i = 0; i < p.size(); i++)
			printf("%d%c", p[i], i == p.size() - 1 ? '\n' : ' ');
	}
	return 0;
}

