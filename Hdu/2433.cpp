/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/21 20:11:40
 * File Name: 2433.cpp
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

#define inf (1 << 20)
#define maxn 105
int n, m;
int adj[maxn][maxn], s[maxn], dis[maxn], mk[maxn][6005];
int to[6005], prev[6005], vis[6005];
int last[maxn], num;
int q[maxn * maxn];
//queue<int> q;

void addEdge(int u, int v) {
    to[num] = v; vis[num] = true; prev[num] = last[u]; last[u] = num++;
}

int bfs(int st, int check) {
    for (int i = 0; i < n; i++)
        dis[i] = inf;
    dis[st] = 0;
    int head = 0, tail = 0, sum = 0, cnt = 0;
//    q.push(st);
    q[tail++] = st;
    while (head < tail) {
//        int u = q.front(); q.pop();
        int u = q[head++];
        sum += dis[u];
        cnt++;
        for (int i = last[u], v; i != -1; i = prev[i])
            if (vis[i] && dis[u] + 1 < dis[v = to[i]]) {
                dis[v] = dis[u] + 1;
                if (check) mk[st][i] = 1;
//                q.push(v);
                q[tail++] = to[i];
            }
    }
    if (cnt == n) return sum;
    return -1;
}

int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        num = 0;
        memset(last, -1, sizeof(last));
        memset(mk, 0, sizeof(mk));
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--; b--;
            addEdge(a, b);
            addEdge(b, a);
        }
        for (int i = 0; i < n; i++) {
            s[i] = bfs(i, 1);
        }
        int ret, rt;
        for (int i = 0; i < m; i++) {
            ret = 0;
            for (int j = 0; j < n; j++) {
                if (!mk[j][i*2] && !mk[j][i*2+1]) {
                    ret += s[j];
                } else {
                    vis[i*2] = vis[i*2+1] = false;
                    rt = bfs(j, 0);
                    vis[i*2] = vis[i*2+1] = true;
                    if (rt == -1) {
                        ret = -1;
                        break;
                    } else ret += rt;
                }
            }
            if (ret == -1) puts("INF");
            else printf("%d\n", ret);
        }
    }
    return 0;
}

