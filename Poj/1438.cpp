/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/13 9:42:15
 * File Name: 1438.cpp
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
/**
 * 求解双连通分支！两点之间可以有重边，这样的话会将两点设为一个连通分支里面，但还是要甚用重边！
 * 所点后的树不会有重边！！
 * 缩点后的树的边也是关于^对偶
 * 判断某边是否为桥的方法是：id[a]!=id[b]并且brg[该边]=壹
 * 并查集+LCA也可以解决双连通分支，而且是动态的！
 */
#define maxn 2010
#define maxm 10100
bool adj[maxn][maxn];
int n, m, dep;
int dfn[maxn], low[maxn];

void Tarjan(int u, int fa) {
    dfn[u] = low[u] = dep++;
    for (int i = 0; i < n; i++) {
        if ((adj[u][i] || adj[i][u]) && i != fa) {
            if (dfn[i] == -1) {
                Tarjan(i, u);
                low[u] = min(low[u], low[i]);
                if (low[i] > dfn[u]) {
                    printf("%d %d 2\n", u + 1, i + 1);
                    adj[u][i] = adj[i][u] = false;
                }
            } else {
                low[u] = min(low[u], dfn[i]);
            }
        }
    }
}

void dfs(int u, int fa) {
    dfn[u] = low[u] = dep++;
    for (int i = 0; i < n; i++)
        if (adj[u][i] && i != fa) {
            if (dfn[i] == -1) {
                dfs(i, u);
                low[u] = min(low[u], low[i]);
                if (adj[u][i] && adj[i][u]) {
                    if (low[i] > dfn[u]) {
                        printf("%d %d 1\n", i + 1, u + 1);
                        adj[i][u] = false;
                    } else {
                        printf("%d %d 1\n", u + 1, i + 1);
                        adj[u][i] = false;
                    }
                }
            } else {
                low[u] = min(low[u], dfn[i]);
                if (adj[u][i] && adj[i][u]) {
                    adj[u][i] = false;
                    printf("%d %d 1\n", u + 1, i + 1);
                }
            }
        }
}

void init() {
    memset(dfn, -1, sizeof(dfn));
    dep = 0;
}

int main() {
    freopen("in.txt", "r", stdin);
    memset(adj, 0, sizeof(adj));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        adj[u][v] = true;
        if (w == 2) adj[v][u] = true;
    }
    init();
    Tarjan(0, -1);
    init();
    for (int i = 0; i < n; i++)
        if (dfn[i] == -1) dfs(i, -1);
    return 0;
}

