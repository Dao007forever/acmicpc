/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/20 13:27:54
 * File Name: 1698.cpp
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
const int MAXN = 400 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    int mk[MAXN];
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] = val;
    }
    int sap(const int idx, const int maxCap)
    {
        if (idx == sink)
            return maxCap;
        int l = maxCap, d, minH = n;
        for (int i = 0; i < n; i++)
        {
            if (cap[idx][i] - flow[idx][i] > 0)
            {
                if (h[idx] == h[i] + 1)
                {
                    d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
                    flow[idx][i] += d;
                    flow[i][idx] -= d;
                    l -= d;
                    if (h[source] == n || l == 0) return maxCap - l;
                }
                minH = min(minH, h[i] + 1);
            }
        }
        if (l == maxCap)
        {
            vh[h[idx]]--;
            vh[minH]++;
            if (vh[h[idx]] == 0)
                h[source] = n;
            h[idx] = minH;
        }
        return maxCap - l;
    }
    int solve(int source, int sink)
    {
        if (source == sink) return inf;
        this->sink = sink;
        this->source = source;
        memset(flow, 0, sizeof(flow));
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        int ans = 0;
        while (h[source] != n)
            ans += sap(source, inf);
        return ans;
    }

}mf;

int week[10];
int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        int n, d, w;
        scanf("%d", &n);
        mf.init(372);
        int source = 0, sink = 371, sum = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 7; j++) {
                scanf("%d", &week[j]);
            }
            scanf("%d%d", &d, &w);
            sum += d;
            mf.addCap(source, i, d);
            for (int j = 1; j <= 7; j++)
                if (week[j]) {
                    for (int k = 0; k < w; k++) {
                        int id = n + k * 7 + j;
                        mf.addCap(i, id, 1);
                        mf.addCap(id, sink, 1);
                    }
                }
        }
        int maxflow = mf.solve(source, sink);
        if (maxflow == sum) puts("Yes");
        else puts("No");
    }
    return 0;
}
