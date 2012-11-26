/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/21 10:12:21
 * File Name: 2832.cpp
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
#define maxn 10005
#define maxm 50005
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init() {
		for (int i = 0; i < maxn; i++) {
			rank[i] = 1;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
            rank[x] += rank[y];
		}
		else {
			parent[x] = y;
            rank[y] += rank[x];
		}
	}
    int size(int x) {
        return rank[Find(x)];
    }
}dsu;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &p) const {
        return w < p.w;
    }
}edge[maxm];
int n, m, q;
int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d%d%d", &n, &m, &q)) {
        dsu.init();
        vector<int> weigh(m + 2), ans(m + 2);
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
            edge[i].u--; edge[i].v--;
        }
        sort(edge, edge + m);

        int sum = 0;
        for (int i = 0; i < m; i++) {
            int w = edge[i].w;
            int pu = dsu.Find(edge[i].u), pv = dsu.Find(edge[i].v);
            if (pu != pv) {
                sum += dsu.size(pu) * dsu.size(pv);
                dsu.Union(pu, pv);
            }
            weigh[i + 1] = w;
            ans[i + 1] = sum;
        }
        weigh[m + 1] = 1000000000;
        ans[m + 1] = sum;

        while (q--) {
            int A;
            scanf("%d", &A);
            int id = upper_bound(weigh.begin(), weigh.end(), A) - weigh.begin() - 1;
            printf("%d\n", ans[id]);
        }
    }
    return 0;
}

