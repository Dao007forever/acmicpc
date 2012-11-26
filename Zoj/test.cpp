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
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;
#define maxV 810
#define maxE 40010
#define INF 0x3f3f3f3f
struct Dinic {
	int V, E;
	int last[maxV], prev[maxE], to[maxE], flow[maxE], cap[maxE];
	int S, T, level[maxV], q[maxV], uesd[maxV], mk[maxV];
	void init(int n)
	{
		V = n; E = 0;
    	memset(last, -1, sizeof(last));
	}	
	void addEdge(int x, int y, int z)
	{
    	to[E] = y, cap[E] = z; flow[E] = 0;
    	prev[E] = last[x], last[x] = E; E++;    
	}

    bool bfs(int s, int t) {
		int i, j, rear = 0;
    	memset(level, -1, sizeof(level));
    	level[s] = 0, q[rear ++] = s;
    	for(i = 0; i < rear; i ++)
        	for(j = last[q[i]]; j != -1; j = prev[j])
            	if(cap[j] - flow[j] && level[to[j]] == -1)
            	{
                	level[to[j]] = level[q[i]] + 1;
                	q[rear ++] = to[j];
                	if(to[j] == t) return 1;    
            	}
    	return 0;
	}
	int dfs(int cur, int t, int f)
	{
/*    if(cur == T) return a;
    for(int &i = uesd[cur]; i != -1; i = prev[i])
        if(flow[i] && d[v[i]] == d[cur] + 1)
            if(int t = dfs(v[i], std::min(a, flow[i])))
            {
                flow[i] -= t, flow[i ^ 1] += t;
                return t;    
            }    
    return 0;*/
    	if (cur == t) return f;
		for (int &i = uesd[cur]; i != -1; i = prev[i])
			if (cap[i] - flow[i] && level[to[i]] == level[cur] + 1) {
				int tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}
	void solve(int s, int t)
	{
    	while(bfs(s, t))
    	{
	    	for (int i = 0; i < V; i++)
    			uesd[i] = last[i];
        	while(dfs(s, t, INF));    
    	}    
	}
	void tra(int cur, int k)
	{
	    int i;
	    mk[cur] = 1;
	    for(i = last[cur]; i != -1; i = prev[i])
        	if(cap[i ^ k] - flow[i ^ k] != 0 && !mk[to[i]])
	            tra(to[i], k);
	}
	bool check(int s, int t)
	{
		memset(mk, 0, sizeof(mk));
		tra(s, 0);
		tra(t, 1);
    	for(int i = 0; i < V; i ++) 
    		if(!mk[i]) return false;
    	return true;    
	}
}mf;
int main()
{
	int N, M, S, T;
    while(scanf("%d%d%d%d", &N, &M, &S, &T), N)
    {
    	S--; T--;
        mf.init(N);
        for(int i = 0; i < M; i ++)
    	{
    		int a, b, c;
        	scanf("%d%d%d", &a, &b, &c);
        	a--; b--;
        	mf.addEdge(a, b, c);
        	mf.addEdge(b, a, c);    
    	}
        mf.solve(S, T);    
        printf("%s\n", mf.check(S, T) ? "UNIQUE" : "AMBIGUOUS");
    }
    return 0;    
}