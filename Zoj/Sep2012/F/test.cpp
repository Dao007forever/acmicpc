#include <map>
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

#define MAXX 50005
#define MAXN 50005
LL set[MAXX],Min[MAXX],Max[MAXX],up[MAXX],down[MAXX];
std::list<LL>edge[MAXX];
std::list<std::pair<LL,LL> >q[MAXX];
bool done[MAXX];
LL ans[MAXX];
LL n,m,i,j,k;
struct DisJointSet{
	LL rank[MAXN], parent[MAXN];

	void init(LL n) {
		for (LL i = 0; i <= n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	LL Find(LL x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(LL x, LL y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}

	LL count(LL n) {
		LL ret = 0;
		for (LL i = 0; i < n; i++)
			ret += parent[i] == i;
		return ret;
	}
}dsu;
struct node
{
    LL a,b,id;
    node(){}
    node(const LL &aa,const LL &bb,const LL &idd): a(aa),b(bb),id(idd) {}
};

std::list<node>to[MAXX];

LL find(const LL &a)
{
    if(set[a]==a)
        return a;
    LL b=set[a];
    set[a]=find(set[a]);
    up[a]=std::max(Max[b]-Min[a],std::max(up[a],up[b]));
    down[a]=std::max(Max[a]-Min[b],std::max(down[a],down[b]));
    Max[a]=std::max(Max[a],Max[b]);
    Min[a]=std::min(Min[a],Min[b]);
    return set[a];
}

void tarjan(const LL &now)
{
    done[now]=true;
    for(std::list<std::pair<LL,LL> >::const_iterator it(q[now].begin());it!=q[now].end();++it)
        if(done[it->first])
            if(it->second>0)
                to[find(it->first)].push_back(node(now,it->first,it->second));
            else
                to[find(it->first)].push_back(node(it->first,now,-it->second));
    for(std::list<LL>::const_iterator it(edge[now].begin());it!=edge[now].end();++it)
        if(!done[*it])
        {
            tarjan(*it);
            set[*it]=now;
        }
    for(std::list<node>::const_iterator it(to[now].begin());it!=to[now].end();++it)
    {
        find(it->a);
        find(it->b);
        ans[it->id]=std::max(up[it->a],std::max(down[it->b],Max[it->b]-Min[it->a]));
    }
}

struct oriEdge {
	LL u, v;
	LL w;
	bool operator < (const oriEdge &p) const {
		return w > p.w;
	}
}orie[MAXN];
void kruskal() {
	dsu.init(n);
	LL sum = 0;
	sort(orie, orie + m);
	for (LL i = 0; i < m; i++) {
		LL u = orie[i].u, v = orie[i].v;
		if (dsu.Find(u) != dsu.Find(v)) {
			sum += orie[i].w;
			//cout << u << " " << v << endl;
        edge[u].push_back(v);
        edge[v].push_back(u);
			dsu.Union(u, v);
		}
	}
	cout << sum << endl;
	//prLLf("%d\n", sum);
}
void init() {
	for (int i = 0; i < MAXN; i++) {
		q[i].clear(); 
		edge[i].clear();
		up[i] = down[i] = set[i] = done[i] = 0;
	}
}
int main()
{
//    freopen("asdf","r",stdin);
    //scanf("%d",&n);
    while (cin >> n) {
    	init();
    for(i=1;i<=n;++i)
    {
        set[i]=i;
        cin >> Min[i];
        //scanf("%d",Min+i);
        Max[i]=Min[i];
    }
    /*for(i=1;i<n;++i)
    {
        scanf("%d %d",&j,&k);
        edge[j].push_back(k);
        edge[k].push_back(j);
    }*/
    cin >> m;
    for (LL i = 0; i < m; i++) {
			//scanf("%d%d%d", &orie[i].u, &orie[i].v, &orie[i].w);
			cin >> orie[i].u >> orie[i].v >> orie[i].w;
		}
		kruskal();
    int query;
    scanf("%d",&query);
    for(int i=1;i<=query;++i)
    {
        //scanf("%d %d",&j,&k);
        cin >> j >> k;
        q[j].push_back(std::make_pair(k,i));
        q[k].push_back(std::make_pair(j,-i));
    }
    tarjan(1);
    for(int i=1;i<=query;++i)
    	cout << ans[i] << endl;
        //printf("%d\n",ans[i]);
	}
    return 0;
}