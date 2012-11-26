/*
 * Author: Yang Zhang
 * Created Time: Wed 05 Sep 2012 09:51:39 PM CST
 * File Name: 1553_BACKUP.cpp
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
const LL inf = 1ll << 60;
int n, k;
int Prev[MAXN], Next[MAXN];
int a[MAXN];
LL cost[MAXN];
bool vis[MAXN];
set<pair<LL, int> > st;

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		st.clear();
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", a+i);

		for (int i = 1; i < n; i++) {
			Prev[i] = i - 1; Next[i] = i + 1;
			cost[i] = a[i + 1] - a[i];
			vis[i] = true;
			st.insert(MP(cost[i], i));
		}
		cost[0] = cost[n] = inf;
		LL ret = 0;
		while (k--) {
			pair<int, int> t;
			do {
				t = *st.begin(); st.erase(st.begin());
			} while (!vis[t.second]);
			int id = t.second;
			ret += t.first;
			int l = Prev[id], r = Next[id];
			vis[l] = vis[r] = false;
			Prev[Next[r]] = id;
			Next[Prev[l]] = id;

			cost[id] = cost[l] + cost[r] - cost[id];
			Prev[id] = Prev[l];
			Next[id] = Next[r];
			st.insert(MP(cost[id], id));
		}
		printf("%lld\n", ret);
		//cout << ret << endl;
	}
	return 0;
}

