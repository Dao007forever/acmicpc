/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/13 19:09:51
 * File Name: 1806.cpp
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

#define maxn 50005
#define maxm 5000005
const int inf = 1 << 30;
int n;
int dist[11];
char name[maxn][20];
map<string, int> mp;
struct Edge {
	int v, next, w;
};
struct node {
    int v, w;
    bool operator < (const node &b) const {
        return w > b.w;
    }
};
priority_queue<node> q;
int cnt;
int ans[maxn];
struct Graph {

	int N, M;
	Edge edge[maxm * 2];
	int num, Head[maxn];
	int dis[maxn], pre[maxn];
    bool vis[maxn];

	Graph() {}

	void init(int N) {
		this->N = N;
		num = 0;
		memset(Head, -1, sizeof(Head));
	}

	void addEdge(int u, int v, int w) {
		edge[num].v = v;
		edge[num].w = w;
		edge[num].next = Head[u];
		Head[u] = num++;
	}

    int dijkstra(int st, int ed) {
        memset(dis, -1, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        node h;
        h.v = st; h.w = 0;
        pre[st] = -1;
        dis[st] = 0;
        while (!q.empty()) q.pop();
        q.push(h);
        while (!q.empty()) {
            node h = q.top(); q.pop();
            if (!vis[h.v]) {
                vis[h.v] = 1;
                for (int i = Head[h.v]; i != -1; i = edge[i].next) {
                    int v = edge[i].v;
                    if (!vis[v] && (dis[v] == -1 || dis[h.v] + edge[i].w < dis[v])) {
                        node nxt;
                        nxt.v = v; nxt.w = dis[h.v] + edge[i].w;
                        dis[v] = nxt.w;
                        pre[v] = h.v;
                        q.push(nxt);
                    }
                }
            }
        }
        return dis[ed];
    }

    /*int SPFA(int st, int ed) {
		for (int i = 1; i <= N; i++) {
			dis[i] = inf;
			vis[i] = false;
		}
        pre[st] = -1;
		vis[st] = true;
		dis[st] = 0;
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = false;
			for (int i = Head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v;
				if (dis[u] + edge[i].w < dis[v]) {
					dis[v] = dis[u] + edge[i].w;
                    pre[v] = u;
					if (!vis[v]) {
						vis[v] = true;
						Q.push(v);
					}
				}
			}
		}
		return dis[ed];
	}*/

    void output(int ed) {
        cnt = 0;
        for (int i = ed; i != -1; i = pre[i])
            ans[cnt++] = i;
        reverse(ans, ans + cnt);
        printf("%d\n", cnt);
        for (int i = 0; i < cnt; i++)
            printf("%d%c", ans[i], i == cnt - 1 ? '\n' : ' ');
    }
}g;

void build() {
    for (int i = 1; i <= n; i++) {
        map<string, int>::iterator pos;
        for (int j = 0; j < 10; j++) {
            int pre = name[i][j];
            for (int k = '0'; k <= '9'; k++) {
                if (k == name[i][j]) continue;
                name[i][j] = k;
                pos = mp.find(name[i]);
                if (pos != mp.end()) {
                    int num = pos->second;
                    g.addEdge(i, num, dist[j]);
                }
                name[i][j] = pre;
            }
        }
        for (int j = 0; j < 10; j++)
            for (int k = j + 1; k < 10; k++) {
                if (name[i][j] == name[i][k]) continue;
                swap(name[i][j], name[i][k]);
                pos = mp.find(name[i]);
                if (pos != mp.end()) {
                    int num = pos->second;
                    g.addEdge(i, num, dist[j]);
                }
                swap(name[i][j], name[i][k]);
            }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < 10; i++)
        scanf("%d", &dist[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%s", name[i]);
        mp[name[i]] = i;
    }
    g.init(n);
    build();
    int ret = g.dijkstra(1, n);
    if (ret == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", ret);
        g.output(n);
    }
    return 0;
}
