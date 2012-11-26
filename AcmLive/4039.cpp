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
#define maxm 500000
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

int n, m;
int g[105][105];
int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				g[i][j] = i == j ? 0 : inf;
			}
		vector<pair<int, int> > edge;
		vector<int> weight;
		vector<int> deg(n + 3);
		int ret = 0;
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			edge.PB(MP(a, b));
			weight.PB(c);
			deg[a]++; deg[b]++;
			ret += c;
			if (c < g[a][b]) {
				g[a][b] = g[b][a] = c;
			}
		}

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (i != j && j != k && k != i) 
						g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

		mcmf.init(2 * n + 2);
		int source = 0, sink = 2 * n + 1;
		for (int i = 1; i <= n; i++) {
			if (deg[i] & 1) {
				mcmf.addCap(source, i, 1, 0);
				mcmf.addCap(i + n, sink, 1, 0);
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j && (deg[i] & 1) && (deg[j] & 1) && g[i][j] < inf) {
					mcmf.addCap(i, j + n, 1, g[i][j]);
				}
		int ans = mcmf.solve(source, sink).second;
		printf("%d\n", ret + ans / 2);
		scanf("%d", &ans);
	}
	return 0;
}