/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/19 21:21:42
 * File Name: 3229.cpp
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
#define maxn 2005
#define maxm 1000005
#define inf (1 << 28)
#define th(x)	this->x = x
struct Nod {
	int b, next;
	int cap, flow, low;
	void init(int b, int low, int up, int next) {
		th(b);	th(low);	cap=up-low;	th(next);
	}
};
struct BoundFlow {
	int E[maxn], n;
	int h[maxn], vh[maxn], source, sink;
	Nod buf[maxm];	int len;	//资源所在
	int lowSumIn[maxn], lowSumOut[maxn];
	void init(int n) {
		this->n = n;
		len = 0;
		memset(E, 255, sizeof(E));
		memset(lowSumIn, 0, sizeof(lowSumIn));
		memset(lowSumOut,0, sizeof(lowSumOut));
	}
	void addCap(int i, int j, int low, int up) {
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
	int sap(const int idx, const int maxCap) {
		if(idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for(int i = E[idx]; i != -1; i = buf[i].next) {
			Nod & nod = buf[i];
			if(nod.cap-nod.flow > 0) {
				if(h[idx]==h[nod.b]+1) {
					d = sap(nod.b, min(l, nod.cap-nod.flow));
					nod.flow += d;
					buf[i ^ 1].flow -= d;//i^壹是i的伙伴
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
			ans += sap(source, inf);
		return ans;
	}
	int solve(int source, int sink, int mn) {			//主程序开始
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
		if(total != ans)	{
            puts("-1");
            return -1;
        }			//无可行流，返回
		solveSAP(source, sink);					//求最大流
//如果要求可行流，去掉此句。如果要求最小流，二分枚举sink到source的下界
		ans = 0;
		for(int i = 0; i < len; i ++) {
			buf[i].flow += buf[i].low;			//附加上low流量
			if(buf[i].b==sink)	ans += buf[i].flow;//统计流量
		}
		//return ans;
        printf("%d\n", ans);
        vector<int> ret;
        for (int i = 1; i <= mn; i++) {
            ret.clear();
            for (int j = E[i]; j != -1; j = buf[j].next)
                if (!(j & 1)) ret.PB(buf[j].flow);
            for (int j = ret.size() - 1; j >= 0; j--)
                printf("%d\n", ret[j]);
        }
	}
};
BoundFlow bf;

int n, m;
int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        bf.init(n + m + 2);
        int source = 0, sink = n + m + 1;
        for (int i = 1; i <= m; i++) {
            int g;
            scanf("%d", &g);
            bf.addCap(i + n, sink, g, inf);
        }
        for (int i = 1; i <= n; i++) {
            int a, b, c, d, v;
            scanf("%d%d", &c, &d);
            bf.addCap(source, i, 0, d);
            while (c--) {
                scanf("%d%d%d", &v, &a, &b);
                bf.addCap(i, n + v + 1, a, b);
            }
        }
        bf.solve(source, sink, n);
        puts("");
    }
    return 0;
}

