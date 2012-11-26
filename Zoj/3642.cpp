/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 08:46:49 PM CST
 * File Name: 3642.cpp
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
/*#define maxV 505
#define maxm 10005
const int inf = 0x3f3f3f3f;
#define th(x)	this->x = x
struct Nod {
	int b, next;
	int cap, flow, low;
	void init(int b, int low, int up, int next) {
		th(b);	th(low);	cap=up-low;	th(next);
	}
};
struct BoundFlow {
	int E[maxV], n;
	int h[maxV], vh[maxV], source, sink;
	Nod buf[maxm];	int len;	//资源所在
	int lowSumIn[maxV], lowSumOut[maxV];
	void init(int n) {
		this->n = n;
		len = 0;
		memset(E, 255, sizeof(E));
		memset(lowSumIn, 0, sizeof(lowSumIn));
		memset(lowSumOut,0, sizeof(lowSumOut));
	}
	void addCap(int i, int j, int low, int up) {
		//cout << i << " " << j << " " << low << " " << up << endl;
		buf[len].init(j, low, up, E[i]);
		E[i] = len++;
		buf[len].init(i, 0, 0, E[j]);
		E[j] = len++;
		lowSumIn[j] += low;
		lowSumOut[i] += low;
	}
	void popCap(int i, int j) {
		E[j] = buf[E[j]].next;
		E[i] = buf[E[i]].next;
		len -= 2;
	}
	int bf(const int idx, const int maxCap) {
		if(idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for(int i = E[idx]; i != -1; i = buf[i].next) {
			Nod & nod = buf[i];
			if(nod.cap-nod.flow > 0) {
				if(h[idx]==h[nod.b]+1) {
					d = bf(nod.b, min(l, nod.cap-nod.flow));
					nod.flow += d;
					buf[i ^ 1].flow -= d;//i^1是i的伙伴
					l -= d;
					if(h[source]==n||l==0) return maxCap-l;
				}
				minH=min(minH, h[nod.b]+1);
			}
		}
		if(l == maxCap) {
			vh[h[idx]] --;
			vh[minH] ++;
			if(vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	int solveSAP(int source, int sink) {
		if(source == sink)	return inf;
		th(source);	th(sink);
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		//for(int i = 0; i < len; i ++)	buf[i].flow = 0;//去掉
		int ans = 0;
		while(h[source] != n)
			ans += bf(source, inf);
		return ans;
	}
	int solve(int source, int sink) {			//主程序开始
		int total = 0;
		for(int i = 0; i < n; i ++) {			//添加①
			addCap(i, n+1, 0, lowSumOut[i]);
			addCap(n, i, 0, lowSumIn[i]);
			total += lowSumIn[i];
		}
		n += 2;									//添加②
		addCap(sink, source, 0, inf);			//添加③
		for(int i = 0; i < len; i ++)	buf[i].flow = 0;
		int ans = solveSAP(n-2, n-1);			//***求解可行流
		popCap(sink, source);					//恢复③
		n -= 2;									//恢复②
		for(int i = n-1; i >= 0; i --) {		//恢复①
			popCap(n, i);
			popCap(i, n+1);
		}
		if(total != ans)	return -1;			//无可行流，返回
		solveSAP(source, sink);					//求最大流
//如果要求可行流，去掉此句。如果要求最小流，二分枚举sink到source的下界
		ans = 0;
		for(int i = 0; i < len; i ++) {
			buf[i].flow += buf[i].low;			//附加上low流量
			if(buf[i].b==sink)	ans += buf[i].flow;//统计流量
		}
		return ans;
	}
}bf;*/
typedef int F;
#define inf (1 << 29)
#define maxV 610
#define maxE 400000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, int f) {
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	bool bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return (level[t] != -1);
	}

	F dfs(int v, int t, F f) {
		if (v == t) return f;
		for (int i = used[v]; i != -1; used[v] = i = prev[i])
			if (level[to[i]] > level[v] && cap[i] > flow[i]) {
				F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}

	F solve(int s, int t) {
		while (bfs(s, t)) {
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return ans;
	}
}mf;

int n, m, num;
int a[maxV], b[maxV], c[maxV];
vector<int> p[maxV];
map<int, int> mp;
int main() {
	while (~scanf("%d", &n)) {
		mp.clear(); m = 0;
		for (int i = 0; i <= n; i++) p[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
			for (int j = 0; j < a[i]; j++) {
				int x;
				scanf("%d", &x);
				p[i].PB(x);
				if (mp.find(x) == mp.end()) {
					mp[x] = ++m;
				}
			}
		}
		scanf("%d", &num);
//		bf.init(n + m + 2);
		mf.init(n + m + 2);
		int source = 0, sink = n + m + 1;
		for (int i = 1; i <= n; i++) {
			if (i == num) {
//				bf.addCap(source, i, 0, inf);
				mf.addCap(source, i, inf);
			}
			else {
//				bf.addCap(source, i, b[i], c[i]);
				mf.addCap(source, i, c[i]);
			}
			for (int j = 0; j < a[i]; j++) {
				int idx = mp[p[i][j]];
//				bf.addCap(i, n + idx, 0, 1);
				mf.addCap(i, n + idx, 1);
			}
		}
		for (int i = 1; i <= m; i++) {
//			bf.addCap(n + i, sink, 0, 1);
			mf.addCap(n + i, sink, 1);
		}
//		int ret = bf.solve(source, sink);
		int ret = mf.solve(source, sink);
		printf("%d\n", ret);
	}
	return 0;
}

