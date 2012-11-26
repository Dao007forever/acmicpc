#define maxn 20005
#define maxm 2000005
#define th(x) this->x = x
const int inf = 0x3f3f3f3f;
struct Nod {
	int b, cap, flow, cost, next;
	void init(int b, int cap, int cost, int next) {
		th(b);	th(cap);	th(cost);	th(next);
	}
};
struct ZKW {
	int E[maxn], n;	//图的所在
	int pi[maxn],source,sink,flow,cost;//顶标,源,汇,最大流,最小费
	bool vis[maxn];	//访问过吗？
	Nod buf[maxm];	int len;//资源
	void init(int n) {
		th(n);
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addCap(int i, int j, int cap, int cst) {
		buf[len].init(j, cap, cst, E[i]);
		E[i] = len ++;
		buf[len].init(i, 0, -cst, E[j]);
		E[j] = len ++;
	}
	int aug(int idx, int maxCap) {
		if(idx == sink) {
			cost+=pi[source]*maxCap;
			flow += maxCap;
			return maxCap;
		}
		vis[idx] = true;
		for(int i = E[idx]; i != -1; i = buf[i].next) {
			Nod & nod = buf[i];
			if(nod.cap-nod.flow>0&&!vis[nod.b]&&pi[nod.b]+nod.cost==pi[idx]){
				if(int d = aug(nod.b, min(maxCap, nod.cap-nod.flow))) {
					nod.flow += d;
					buf[i^1].flow -= d;
					return d;
				}
			}
		}
		return 0;
	}
	bool modLabel() {
		int d = inf;
		for(int i = 0; i < n; i ++)	if(vis[i]) {
			for(int j = E[i]; j != -1; j = buf[j].next) {
				Nod & nod = buf[j];
				if(nod.cap-nod.flow>0 && !vis[nod.b]) {
					d = min(d, nod.cost-pi[i]+pi[nod.b]);
				}
			}
		}
		if(d == inf)	return false;
		for(int i = 0; i < n; i ++)	if(vis[i])	pi[i] += d;
		return true;
	}
	int solve(int source, int sink) {
		th(source);	th(sink);
		flow = cost = 0;
		memset(pi, 0, sizeof(pi));
		for(int i = 0; i < len; i ++)	buf[i].flow = 0;
		do do memset(vis, 0, sizeof(vis));
			while(aug(source, inf));
		while(modLabel());
		return cost;
	}
};

