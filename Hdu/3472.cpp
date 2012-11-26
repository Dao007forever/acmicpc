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
const int MAXN = 100 + 10;
const int inf = 0x3f3f3f3f;
const int N = 26;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN];
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

bool pos[MAXN], mat[MAXN][MAXN], vst[MAXN];
int indeg[MAXN], outdeg[MAXN];

void init() {
	sap.init(N + 2);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char st[22];
		int x;
		scanf("%s %d", st, &x);
		int len = strlen(st);
		int u = st[0] - 'a', v = st[len - 1] - 'a';
		outdeg[u]++;
		indeg[v]++;
		pos[u] = pos[v] = true;
		mat[u][v] = mat[v][u] = true;
		if (x) sap.addCap(u, v, 1);
	}
}

void dfs(int u) {
	vst[u] = true;
	for (int i = 0; i < N; i++)
		if (!vst[i] && mat[u][i]) dfs(i);
}

void work() {
	for (int i = 0; i < N; i++)
		if (pos[i]) {
			dfs(i);
			break;
		}
	bool flag = true;
	for (int i = 0; i < N; i++)
		if (pos[i] && !vst[i]) {
			flag = false;
			break;
		}
	if (!flag) {
		puts("Poor boy!");
		return;
	}

	vector<int> p;
	int ss, tt;
	for (int i = 0; i < N; i++) {
		if (abs(outdeg[i] - indeg[i]) & 1) {
			p.PB(i);
			if (outdeg[i] - indeg[i] > 0) ss = i;
			else tt = i;
		}
	}
	if (p.size() > 2 || p.size() == 1) {
		puts("Poor boy!");
		return;
	}

	int source = N, sink = N + 1;
	if (p.size() == 2)
		sap.addCap(ss, tt, 1);
	int sum = 0;
	for (int i = 0; i < N; i++) {
		int x = (outdeg[i] - indeg[i]) / 2;
		if (x) {
			sap.addCap(source, i, x);
			sum += x;
		} else {
			sap.addCap(i, sink, -x);
		}
	}
	int ret = sap.solve(source, sink);
	if (ret == sum) {
		puts("Well done!");
	} else {
		puts("Poor boy");
	}
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		memset(vst, 0, sizeof(vst));
		memset(mat, 0, sizeof(mat));
		memset(pos, 0, sizeof(pos));
		memset(indeg, 0, sizeof(indeg));
		memset(outdeg, 0, sizeof(outdeg));
		init();
		work();
	}
	return 0;
}
