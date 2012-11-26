/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/13 21:11:53
 * File Name: 2699.cpp
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

const int MAXN = 100 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] += val;
        g[i][j] = 1;
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

}sap;

vector<int> win;
int sum;
map<pair<int, int>, int> mp;

void work() {
    int Max = 0, ret = 0, cnt = 0, n = SZ(win);
    for (int i = 0; i < n; i++)
        Max = max(Max, win[i]);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            mp[MP(i, j)] = ++cnt;
        }
    for (int st = 0; st < (1 << n); st++) {
        bool flag = true;
        for (int i = 0; i < n; i++)
            if (win[i] == Max && !(st & (1 << i))) {
                flag = false;
                break;
            }
        if (!flag) continue;
        sap.init(n + cnt + 2);
        int source = 0, sink = n + cnt + 1;
        for (int i = 0; i < n; i++)
            sap.addCap(source, i + 1, win[i]);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int num = mp[MP(i, j)];
                if (win[i] < win[j] && (st & (1 << i))) {
                    sap.addCap(i + 1, n + num, 1);
                } else if (win[j] < win[i] && (st & (1 << j))) {
                    sap.addCap(j + 1, n + num, 1);
                } else {
                    sap.addCap(i + 1, n + num, 1);
                    sap.addCap(j + 1, n + num, 1);
                }
            }
        for (int i = 1; i <= cnt; i++)
            sap.addCap(n + i, sink, 1);
        int flow = sap.solve(source, sink);
        if (flow == sum) {
            int tot = 0;
            for (int i = 0; i < n; i++)
                if (st & (1 << i)) tot++;
            ret = max(ret, tot);
        }
    }
    printf("%d\n", ret);
}
int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d\n", &Test);
    while (Test--) {
        win.clear();
        sum = 0;
        string input;
        getline(cin, input);
        istringstream iss;
        iss.str(input);
        int x;
        while (iss >> x) {
            win.PB(x);
            sum += x;
        }
        if (SZ(win) == 1) {
            puts("1");
            continue;
        }
        work();
    }
    return 0;
}

