/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/1 19:55:50
 * File Name: 3212.cpp
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

const int MAXN = 1005;
int n, m;
vector<int> adj[MAXN];
int ind[MAXN];
int col[MAXN], cnt[3];
bool flag;

void addEdge(int u, int v) {
    adj[u].PB(v);
    adj[v].PB(u);
}

void dfs(int u, int color) {
    if (!flag) return;
    if (col[u]) {
        if (col[u] != color) flag = false;
        return;
    }
    col[u] = color;
    cnt[color]++;
    for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++)
        dfs(*it, 3 - color);
}

int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i <= n; i++)
            adj[i].clear(), col[i] = 0;

        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
        }

        flag = true;
        int ret = 0;
        for (int i = 1; i <= n && flag; i++)
            if (!col[i]) {
                memset(cnt, 0, sizeof(cnt));
                dfs(i, 1);
                ret += min(cnt[1], cnt[2]);
            }

        if (flag) printf("%d\n", ret);
        else printf("Impossible\n");
    }
    return 0;
}

