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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define maxn 110
#define maxm 100010
#define th(x) this->x = x
const LL inf = 1000000000000LL;
struct Nod {
	LL b, cap, flow, cost, next;
	void init(LL b, LL cap, LL cost, LL next) {
		th(b);	th(cap);	th(cost);	th(next);
	}
};
struct ZKW {
	LL E[maxn], n;	//图的所在
	LL pi[maxn],source,sink,flow,cost;//顶标,源,汇,最大流,最小费
	bool vis[maxn];	//访问过吗？
	Nod buf[maxm];	LL len;//资源
	void init(LL n) {
		th(n);
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addCap(LL i, LL j, LL cap, LL cst) {
		buf[len].init(j, cap, cst, E[i]);
		E[i] = len ++;
		buf[len].init(i, 0, -cst, E[j]);
		E[j] = len ++;
	}
	LL aug(LL idx, LL maxCap) {
		if(idx == sink) {
			cost+=pi[source]*maxCap;
			flow += maxCap;
			return maxCap;
		}
		vis[idx] = true;
		for(LL i = E[idx]; i != -1; i = buf[i].next) {
			Nod & nod = buf[i];
			if(nod.cap-nod.flow>0&&!vis[nod.b]&&pi[nod.b]+nod.cost==pi[idx]){
				if(LL d = aug(nod.b, min(maxCap, nod.cap-nod.flow))) {
					nod.flow += d;
					buf[i^1].flow -= d;
					return d;
				}
			}
		}
		return 0;
	}
	bool modLabel() {
		LL d = inf;
		for(LL i = 0; i < n; i ++)	if(vis[i]) {
			for(LL j = E[i]; j != -1; j = buf[j].next) {
				Nod & nod = buf[j];
				if(nod.cap-nod.flow>0 && !vis[nod.b]) {
					d = min(d, nod.cost-pi[i]+pi[nod.b]);
				}
			}
		}
		if(d == inf)	return false;
		for(LL i = 0; i < n; i ++)	if(vis[i])	pi[i] += d;
		return true;
	}
	LL solve(LL source, LL sink) {
		th(source);	th(sink);
		flow = cost = 0;
		memset(pi, 0, sizeof(pi));
		for(LL i = 0; i < len; i ++)	buf[i].flow = 0;
		do do memset(vis, 0, sizeof(vis));
			while(aug(source, inf));
		while(modLabel());
		return cost;
	}
}mc;


int w[maxn], b[maxn];
int mat[maxn][maxn];
LL calcP(LL x) {
	if (x < 60) return 0;
	return 4LL * 1600 - 3LL * (100LL - x) * (100LL - x);
}
int main(int argc, char const *argv[])
{
	int N, K, M;
	while (~scanf("%d%d%d", &N, &K, &M)) {
		if (N == 0 && K == 0 && M == 0) break;
		int sumW = 0;
		for (int i = 1; i <= M; i++) 
			scanf("%d", &w[i]), sumW += w[i];
		for (int i = 1; i <= M; i++)
			scanf("%d", &b[i]);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				scanf("%d", &mat[i][j]);
		mc.init(N + M + 2);
		int source = 0, sink = N + M + 1;
		for (int i = 1; i <= N; i++)
			mc.addCap(source, i, K, 0);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				if (mat[i][j]) {
					mc.addCap(i, N + j, K, 0);
				}
		int sum = 0;
		LL retP = 0;
		for (int j = 1; j <= M; j++) {
			if (b[j] >= 60) {
				retP += calcP(b[j]) * (LL)w[j];
			}
			if (b[j] < 60) {
				sum += 60 - b[j];
				mc.addCap(N + j, sink, 60 - b[j], -inf);
				retP += calcP(60) * (LL)w[j];
			}
			for (int k = max(b[j], 60); k < 100; k++) {
				LL cost = (calcP(k + 1) - calcP(k)) * (LL)w[j];
				mc.addCap(N + j, sink, 1, -cost);
			}
		}
		LL ret = -mc.solve(source, sink);
		if (ret / inf < sum) {
			puts("0.000000");
		} else {
			LL ans = ret % inf;
			ans = ans + retP;
			double final = (double)ans / sumW / 1600.0;
			printf("%.6f\n", final);
		}
	}
	return 0;
}