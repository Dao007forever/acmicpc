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

#define maxn 105
const int inf = 0x3f3f3f3f;
//KM_Slack:O(n^3)
struct KM {
	int E[maxn][maxn], n;		//图的所在，需传入
	int lx[maxn],ly[maxn],xmate[maxn],ymate[maxn];//标号,伙伴
	bool xvis[maxn], yvis[maxn];	//访问过
	int slack[maxn], prev[maxn];	//松弛量,Y中的点的前驱(在X中)
	queue<int> q;				//bfs时的队列
	bool bfs() {
		while(!q.empty()) {
			int p = q.front(), u = p>>1;	q.pop();
			if(p&1) {	//右面节点
				if(ymate[u] == -1){//找到,开始更新路径上的mate,返回
					while(u != -1) {
						ymate[u] = prev[u];
						swap(xmate[prev[u]], u);
					}
					return true;
				} else {	//没找到, 从ymate[u]继续找
					q.push(ymate[u]<<1); xvis[ymate[u]] = true;
				}
			} else {	//左面节点
				for(int i = 0; i < n; i++) {
					if(yvis[i]) continue;
					if(lx[u]+ly[i] == E[u][i]) {//有路径,继续找
						prev[i] = u;
						q.push((i<<1)|1);	yvis[i] = true;
					} else {				//没路径,开始松弛
						int ex = lx[u]+ly[i]-E[u][i];
						if(slack[i] > ex) {
							slack[i] = ex;
							prev[i] = u;
						}
					}
				}
			}
		}
		return false;
	}
	int solve() {
		for(int i = 0; i < n; i ++) {
			ly[i] = 0;
			lx[i] = *max_element(E[i], E[i]+n);
		}
		memset(xmate, 255, sizeof(xmate));
		memset(ymate, 255, sizeof(ymate));
		bool agu = true;
		for(int idx = 0; idx < n; idx += agu) {
			if(agu) {
				memset(xvis, 0, sizeof(xvis));
				memset(yvis, 0, sizeof(yvis));
				memset(slack, 63, sizeof(slack));
				while(!q.empty()) q.pop();
				q.push(idx<<1);	xvis[idx] = true;
			}
			if(agu = bfs())	continue;	//找到一条增广, 进行下一点
			int ex = inf;
			for(int i = 0; i < n; i++)
				if(!yvis[i])	ex = min(ex, slack[i]);
			for(int i = 0; i < n; i++) {
				if(xvis[i]) lx[i] -= ex;
				if(yvis[i]) ly[i] += ex;
				slack[i] -= ex;
				if(!yvis[i] && slack[i] == 0) {
					q.push((i<<1)|1);	yvis[i] = true;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			ans += E[i][xmate[i]];
		}
		return ans;
	}
}km;

const int base = 100;
int n;
int v[maxn], h[maxn], p[maxn], a[maxn], b[maxn];
bool beat(int i, int j) {
	int t1 = p[j] / a[i] + (p[j] % a[i] > 0 ? 1 : 0);
	int t2 = h[i] / b[j] + (h[i] % b[j] > 0 ? 1 : 0);
	if (t1 <= t2) return true;
	return false;
}
int main(int argc, char const *argv[])
{
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &v[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &h[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &p[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &b[i]);
		}
		km.n = n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (beat(i, j)) {
					km.E[i][j] = v[i] * base;
				} else {
					km.E[i][j] = -v[i] * base;
				}
				if (i == j) km.E[i][j]++;
			}
		}
		int ret = km.solve();
		if (ret > 0) {
			int r1 = ret / base;
			double r2 = (double)(ret % base) * 100.0 / n;
			printf("%d %.3f", r1, r2);
			puts("%");
		} else {
			puts("Oh, I lose my dear seaco!");
		}
	}
	return 0;
}