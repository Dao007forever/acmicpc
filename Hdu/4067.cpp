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
    	//cout << a << " " << b << " " << cap << " " << cst << endl;
        buf[len].init(b, E[a], cap, cst);   E[a] = len ++;
        buf[len].init(a, E[b], 0,  -cst);   E[b] = len ++;
    }
    bool spfa(int source, int sink) {
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
        return d[sink] != inf;
    }
    pair<int, int> solve(int source, int sink) {
        int minCost = 0,maxFlow = 0;
        while(spfa(source, sink)) {
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
} mcmf;


int main(int argc, char const *argv[])
{
	int n, m, s, t;
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		scanf("%d%d%d%d", &n, &m, &s, &t);
		vector<int> ind(n + 3, 0), outd(n + 3, 0);
		mcmf.init(n + 2);
		int source = 0, sink = n + 1;
		int sum = 0;
		for (int i = 0; i < m; i++) {
			int u, v, a, b;
			scanf("%d%d%d%d", &u, &v, &a, &b);
			if (a <= b) {
				sum += a;
				ind[v]++; outd[u]++;
				mcmf.addCap(v, u, 1, b - a);
			} else {
				sum += b;
				mcmf.addCap(u, v, 1, a - b);
			}
		}
		ind[s]++; outd[t]++;
		int flow = 0;
		for (int i = 1; i <= n; i++) {
			if (ind[i] > outd[i]) {
				mcmf.addCap(source, i, ind[i] - outd[i], 0);
				flow += ind[i] - outd[i];
			} else {
				mcmf.addCap(i, sink, outd[i] - ind[i], 0);
			}
		}
		pair<int, int> ret = mcmf.solve(source, sink);
		if (ret.first == flow) printf("%d\n", sum + ret.second);
		else puts("impossible");
	}
	return 0;
}