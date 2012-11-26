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

#define maxn 1010
#define maxm 4*maxn
const int inf = 0x3f3f3f3f;
struct Nod {
    int b, nxt;
    int cap, cst;
    void init(int b, int nxt, int cap,int cst) {
        this->b = b;
        this->nxt = nxt;
        this->cap = cap;
        this->cst = cst;
    }
};
struct MinCost {
    int E[maxn];        int n;
    Nod buf[maxm*2];    int len;
    
    int p[maxn];
    void init(int n) {
        this->n = n;
        memset(E, 255, sizeof(E));
        len = 0;
    }
    void addCap(int a, int b, int cap, int cst) {
        buf[len].init(b, E[a], cap, cst);   E[a] = len ++;
        buf[len].init(a, E[b], 0,  -cst);   E[b] = len ++;
    }
    int spfa(int source, int sink) {
        static queue<int> q;
        static int d[maxn];
        memset(d,  63, sizeof(d));
        memset(p, 255, sizeof(p));
        
        d[source] = 0;
        q.push(source);
        int u, v;
        while(!q.empty()) {
            u = q.front();
            q.pop();
            for(int i = E[u]; i != -1; i = buf[i].nxt) {
                v = buf[i].b;
                if(buf[i].cap>0 && d[u]+buf[i].cst<d[v]) {
                    d[v] = d[u]+buf[i].cst;
                    p[v] = i;
                    q.push(v);
                }
            }
        }
        return d[sink];
    }
    pair<int, int> solve(int source, int sink) {
        int minCost = 0,maxFlow = 0;
        while(true) {
        	int tmp = spfa(source, sink);
        	if (tmp >= 0) break;
            int neck = inf;
            for(int t=p[sink]; t != -1; t = p[ buf[t^1].b ])
                neck = min(neck, buf[t].cap);
            maxFlow += neck;
            for(int t = p[sink]; t != -1; t = p[ buf[t^1].b ]) {
                buf[t].cap -= neck;
                buf[t^1].cap += neck;
                minCost += buf[t].cst * neck;
            }
        }
        return MP(maxFlow, minCost);
    }
} mc;


int main(int argc, char const *argv[])
{
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		mc.init(n + 1);
		int source = 0, sink = n;
		for (int i = 1; i < n; i++) {
			int x;
			scanf("%d", &x);
			mc.addCap(i, sink, inf, -x);
		}
		for (int i = 0; i < m; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			a--; b--;
			mc.addCap(a, b, c, d);
			mc.addCap(b, a, c, d);
		}
		pair<int, int> ret = mc.solve(source, sink);
		//cout << ret.first << " " << ret.second << endl;
		printf("%d\n", -ret.second);
	}
	return 0;
}