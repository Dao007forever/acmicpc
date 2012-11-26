/*
 * Author: Yang Zhang
 * Created Time: Fri 31 Aug 2012 09:31:50 PM CST
 * File Name: 3545_NAJKRACI.cpp
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

#define MAXN 3505
#define MAXM 30005
const int inf = 1<<29;
const int mod = 1000000007;
struct Edge {
	int v, w, next;
	LL ret;
}e[MAXM << 1];
int n, m;
int Head[MAXN], E;
int dis[MAXN], path_to[MAXN], path_from[MAXN];

void addEdge(int u, int v, int w) {
	e[E].v = v; e[E].w = w; e[E].ret = 0; e[E].next = Head[u]; Head[u] = E++;
}

//priority_queue<pair<int, int> > q;
struct cmp {
	bool operator () (int a, int b) {
		if (dis[a] != dis[b]) return dis[a] < dis[b];
		return a < b;
	}
};
vector<int> p;
void work(int st) {
	for (int i = 0; i < n; i++) dis[i] = inf;
	set<int, cmp> pq;
	p.clear();
	dis[st] = 0; path_to[st] = 1;
	pq.insert(st);
	//q.push(MP(0, st));
	while (!pq.empty()) {
		int u = *pq.begin(); pq.erase(pq.begin());
		//int u = q.top().second; q.pop();
		p.PB(u);
		for (int i = Head[u]; ~i; i = e[i].next) {
			int v = e[i].v, w = e[i].w;
			if (dis[u] + w > dis[v]) continue;
			if (dis[u] + w < dis[v]) {
				path_to[v] = 0;
				if (dis[v] != inf) pq.erase(v);
				dis[v] = dis[u] + w;
				pq.insert(v);
				//q.push(MP(-dis[v], v));
			}
			path_to[v] = (path_to[v] + path_to[u]) % mod;
		}
	}

	for (int i = p.size() - 1; i >= 0; i--) {
		int u = p[i]; 
		path_from[u] = 1;
		for (int j = Head[u]; ~j; j = e[j].next) {
			int v = e[j].v, w = e[j].w;
			if (dis[u] + w > dis[v]) continue;
			path_from[u] = (path_from[u] + path_from[v]) % mod;
			e[j].ret = (e[j].ret + (LL)path_to[u] * path_from[v]) % mod;
		}
	}
}

int main() {
	for (; ~scanf("%d%d", &n, &m); ) {
		E = 0;
		memset(Head, -1, sizeof(Head));
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			addEdge(a, b, c);
		}
		for (int i = 0; i < n; i++)
			work(i);
		for (int i = 0; i < m; i++) {
			cout << e[i].ret << endl;
//			printf("%d\n", e[i].ret);
		}
	}
	return 0;
}

