/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/11 15:30:58
 * File Name: 3912_MTREECOL.cpp
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

#define MAXN 1005
int n, root;
int c[MAXN], parent[MAXN];
bool vst[MAXN];
int nxt[MAXN], pre[MAXN], rank[MAXN], sum[MAXN];

int find() {
    double Max = 0;
    int flag = -1;
    for (int i = 1; i <= n; i++) {
        if (Max < sum[i] * 1.0 / rank[i] && !vst[i]) {
            Max = sum[i] * 1.0 / rank[i];
            flag = i;
        }
    }
    return flag;
}

void uni(int x) {
    int i;
    for (i = parent[x]; pre[i] != -1; i = pre[i]);
    rank[i] += rank[x];
    sum[i] += sum[x];
    for (i = parent[x]; nxt[i] != -1; i = nxt[i]);
    nxt[i] = x;
    pre[x] = i;
    vst[x] = true;
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &root) && n && root) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", c + i);
            vst[i] = false;
            pre[i] = nxt[i] = -1;
            rank[i] = 1;
            sum[i] = c[i];
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            parent[b] = a;
        }
        vst[root] = true;
        while (true) {
            int u = find();
            if (u == -1) break;
            uni(u);
        }
        int cnt = 0, ret = 0;
        for (int i = root; i != -1; i = nxt[i])
            ret += (++cnt) * c[i];
        printf("%d\n", ret);
    }
    return 0;
}
