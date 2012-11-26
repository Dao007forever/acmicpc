#define maxn 110
#define maxm 10010
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		this->b = b;
		this->nxt = nxt;
	}
};
struct Kosaraju {
	int E[maxn], EN[maxn];	int n;	//原图，反向图
	Nod buf[maxm*2];		int len;	//资源
	
	int id[maxn];		///ndfs时用：原始图中的某个节点所在连通分支编号
	int nScc;			///强连通个数
	
	//以上变量可能会被solve后使用
	int vis[maxn];				///visited
	int order[maxn], order_idx;		///dfs时用：的时间戳
	
	void init(int n) {
		this->n = n;
		memset(E, 255, sizeof(E));
		memset(EN, 255, sizeof(EN));
		len = 0;
	}
	void addEdge(int a, int b) {
		buf[len].init(b, E[a]);		E[a] = len ++;
		buf[len].init(a, EN[b]);	EN[b] = len ++;
	}
	void dfs(int idx) {
		if(vis[idx])	return;
		vis[idx] = true;
		for(int i = E[idx]; i != -1; i = buf[i].nxt)
			dfs(buf[i].b);
		order[order_idx ++] = idx;
	}
	void ndfs(int idx) {
		if(vis[idx])	return;
		vis[idx] = true;
		id[idx] = nScc;
		for(int i = EN[idx];i != -1; i = buf[i].nxt)
			ndfs(buf[i].b);
	}
	void solve() {
		memset(vis, 0, sizeof(vis));
		order_idx = nScc = 0;
			//init over!
		for(int i = 0; i < n; i ++)	dfs(i);
			///dfs over!
		memset(vis, 0, sizeof(vis));
		for(int i = n-1; i >= 0; i --) {
			if(false == vis[order[i]]) {
				ndfs(order[i]);
				nScc ++;
			}
		}
	}
//--------------以上完全是SCC精简版--------------------
	int partner[maxn], stack[maxn];		//某个id的伙伴id,拓排的栈
	int ENScc[maxn];					///缩点后的逆向图
	Nod bufNScc[maxm];	int lenNScc;	///资源
	
	bool sat() {
		solve();
		for(int i = 0; i < n; i += 2) {
			if(id[i] == id[i+1])	return false;
		}
		//--------如果只是判定，这里可以直接返回true, 并且不需要有新增变量-------
		int *inDgr = order, len = 0, now;	//入度，复用order数; 栈大小; 拓扑时当前元素
		for(int i = 0; i < n; i += 2) {
			partner[id[i]] = id[i+1];
			partner[id[i+1]] = id[i];
		}
		///找出自己的伙伴完毕！
		memset(order, 0, sizeof(order));//不解释！
		memset(ENScc, 255, sizeof(ENScc));
		lenNScc = 0;
		
		for(int j = 0; j < n; j ++) {
			for(int i = E[j]; i != -1; i = buf[i].nxt) {
				int b = buf[i].b;
				if(id[j] != id[b]) {
					bufNScc[lenNScc].init( id[j],ENScc[ id[b] ] );
					ENScc[ id[b] ] = lenNScc ++;
					inDgr[ id[j] ] ++;
					//逆向见图，增加入度
				}
			}
		}
		///逆向建图完毕！可能有重边，未处理。。不影响正确性
		memset(vis, 0, sizeof(vis));//0未访问，1合法，2不合法
		///准备完毕，开始拓扑排序!
		for(int i = 0; i < nScc; i ++)
			if(inDgr[i] == 0)
				stack[len ++] = i;
		while(len) {
			now = stack[-- len];
			if(vis[now] == 0) {
				vis[now] = 1;///合法！
				color(partner[now]);///伙伴就不行了！
			}
			for(int i = ENScc[now]; i != -1; i = bufNScc[i].nxt) {
				int b = bufNScc[i].b;
				inDgr[b] --;
				if(inDgr[b] == 0) {
					stack[len ++] = b;
				}
			}
		}
		return true;//可容
	}
	void color(int idx) {
		if(vis[idx])	return;
		vis[idx] = 2;
		for(int i = ENScc[idx]; i != -1; i = bufNScc[i].nxt) {
			color( bufNScc[i].b );
		}
	}
	void output() {//示范性输出
		for(int i = 0; i < n; i ++) {
			if(vis[ id[i] ] == 1) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
} ko;
