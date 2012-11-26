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

const int maxn = 305;
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
		for(int i = 0; i < n; i++)
			ans += E[i][xmate[i]];
		return ans;
	}
}km;

int N, M, K, P;
int st[maxn];
int d[maxn][maxn];
void Floyd() {
	for (int k = 0; k < N + M; k++)
		for (int i = 0; i < N + M; i++)
			for (int j = 0; j < N + M; j++)
				if (i != j && j != k && i != k)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d%d", &N, &M, &K, &P)) {
		for (int i = 0; i < N + M; i++)
			for (int j = 0; j < N + M; j++)
				d[i][j] = i == j ? 0 : inf;
		for (int i = 0; i < N; i++)
			scanf("%d", &st[i]);
		for (int i = 0; i < K; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			d[N + a][N + b] = d[N + b][N + a] = c;
		}
		for (int i = 0; i < P; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			d[N + b][a] = c;
		}
		Floyd();
		km.n = N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				km.E[i][j] = -d[N + st[i] - 1][j];
			}
		}
		int ret = -km.solve();
		printf("%d\n", ret);
	}
	return 0;
}