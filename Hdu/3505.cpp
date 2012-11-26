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
/*------------#include omitted-----------*/
const int MAXN = 500 + 10;
const LL inf = 1LL << 60;
struct SAP
{
    LL cap[MAXN][MAXN], flow[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
    }
    void addCap(int i, int j, LL val)
    {
        cap[i][j] += val;
    }
    int sap(const int idx, const LL maxCap)
    {
        if (idx == sink)
            return maxCap;
        LL l = maxCap, d;
        int minH = n;
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
    LL solve(int source, int sink)
    {
        if (source == sink) return inf;
        this->sink = sink;
        this->source = source;
        memset(flow, 0, sizeof(flow));
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        LL ans = 0;
        while (h[source] != n)
            ans += sap(source, inf);
        return ans;
    }
}sap;

int n, m;
int love[MAXN], hate[MAXN];
LL value[MAXN];
vector<int> adj[MAXN];
struct Trie {
    struct Tnode {
        int next[26];
        int terminate;
    }chd[MAXN * 600];
    int size;

    void init() {
        size = 1;
        memset(chd[0].next, 0, sizeof(chd[0].next));
        chd[0].terminate = -1;
    }

    void insert(char *s, int id) {
        int p = 0;
        for (int i = 0; s[i]; i++) {
            int c = s[i] - 'a';
            if (!chd[p].next[c]) {
                memset(chd[size].next, 0, sizeof(chd[size].next));
                chd[size].terminate = -1;
                chd[p].next[c] = size++;
            }
            p = chd[p].next[c];
        }
        if (chd[p].terminate != -1) {
            love[id] += love[chd[p].terminate];
            hate[id] += hate[chd[p].terminate];
        }
        chd[p].terminate = id;
    }

    void find(char *s, int id) {
        int p = 0;
        for (int i = 0; s[i]; i++) {
            int c = s[i] - 'a';
            if (chd[p].next[c]) {
                p = chd[p].next[c];
                if (chd[p].terminate != -1) {
                    value[id] += love[chd[p].terminate];
                    adj[id].PB(chd[p].terminate);
                }
            } else return;
        }
    }
}trie;

void work() {
    sap.init(n + m + 2);
    int source = 0, sink = n + m + 1;
    LL sum = 0;
    for (int i = 1; i <= m; i++) {
        sap.addCap(source, i, value[i]);
        sum += value[i];
    }
    for (int i = 1; i <= n; i++)
        sap.addCap(m + i, sink, hate[i]);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < adj[i].size(); j++)
            sap.addCap(i, m + adj[i][j], inf);
    }
    LL ret = sap.solve(source, sink);
    cout << sum - ret << endl;
}

int main() {
    int Test;
    scanf("%d", &Test);
    for (int cas = 1; cas <= Test; cas++) {
        printf("Case %d: ", cas);
        scanf("%d%d", &n, &m);
        memset(value, 0, sizeof(value));
        for (int i = 0; i <= m; i++)
            adj[i].clear();
        trie.init();

        for (int i = 1; i <= n; i++) {
            char st[55];
            scanf("%d%d%s", &love[i], &hate[i], st);
            trie.insert(st, i);
        }
        for (int i = 1; i <= m; i++) {
            char st[1111];
            scanf("%s", st);
            int len = strlen(st);
            for (int j = 0; j < len; j++)
                trie.find(st + j, i);
        }

        work();
    }
    return 0;
}
