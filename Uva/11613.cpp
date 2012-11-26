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

#define maxn 1010
#define maxm 100010
const LL inf = 0x3f3f3f3f3f3f3f3f;
struct Nod {
    int b, nxt;
    int cap;
    LL cst;
    void init(int b, int nxt, int cap, LL cst) {
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
    void addCap(int a, int b, int cap, LL cst) {
    	//cout << a << " " << b << " " << cap << " " << cst << endl;
        buf[len].init(b, E[a], cap, cst);   E[a] = len ++;
        buf[len].init(a, E[b], 0,  -cst);   E[b] = len ++;
    }
    int spfa(int source, int sink) {
        static queue<int> q;
        static LL d[maxn];
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
    pair<int, LL> solve(int source, int sink) {
        LL minCost = 0;
        int maxFlow = 0;
        while(true) {
        	LL t = spfa(source, sink);
        	if (t > 0 || t == inf) break;
            int neck = 0x3f3f3f3f;
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

int M, I;

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		scanf("%d%d", &M, &I);
		mcmf.init(2 * M + 2);
		int source = 0, sink = 2 * M + 1;
		for (int i = 1; i <= M; i++) {
			int m, n, p, s, E;
			scanf("%d%d%d%d%d", &m, &n, &p, &s, &E);
			mcmf.addCap(source, i, n, m);
			mcmf.addCap(M + i, sink, s, -p);
			for (int j = 0; j <= E; j++) {
				if (i + j > M) break;
				mcmf.addCap(i, M + i + j, 0x3f3f3f3f, (LL)j * I);
			}
		}
		pair<int, LL> ret = mcmf.solve(source, sink);
		cout << -ret.second << endl;
	}
	return 0;
}