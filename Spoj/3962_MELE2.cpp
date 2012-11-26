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

#define MAXN 100005
LL n;
int p[3];
LL dis[MAXN];
bool vis[MAXN];

int main() {
//	freopen("in", "r", stdin);
	cin >> n >> p[0] >> p[1] >> p[2];
	sort(p, p + 3);
	int mod = p[0];
	for (int i = 0; i <= mod; i++)
		dis[i] = n + 1;
	dis[0] = 0;
	vis[0] = true;
	queue<int> Q;
	Q.push(0);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for (int i = 0; i < 3; i++) {
			int v = (u + p[i]) % mod;
			if (dis[u] + p[i] < dis[v]) {
				dis[v] = dis[u] + p[i];
				if (!vis[v]) {
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}

	n--;
	LL ret = 0;
	for (int i = 0; i < mod; i++)
		if (dis[i] <= n) ret += (n - dis[i]) / mod + 1;
	cout << ret << endl;
}
