#define maxn 50010
#define maxq 75010
#define th(x) this->x = x
//【迷你并查集】
int p[maxn];
void make() {
	memset(p, 255, sizeof(p));
}
int find(int x) {
	int px, i;
	for(px = x; p[px] != -1; px = p[px]);
	while(x != px) {
		i = p[x];
		p[x] = px;
		x = i;
	}
	return px;
}
void unio(int x, int y) {	//让x成为y的父亲, 断言不会出现冲突情况
	p[find(y)] = find(x);
}
//下面是Tarjan开始
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		th(b);	th(nxt);
	}
};
struct Tarjan {
	int n;
	Nod bufT[2*maxn];	int lenT;	int ET[maxn];	//Tree	资源
	Nod bufQ[2*maxq];	int lenQ;	int EQ[maxn];	//Query	询问
	
	int V[2*maxn], route[maxn];					//路径的权，根到某点的路径和
	
	int ans[maxq];							//保存最后的结果，按照输入顺序保存
	char vis[maxn];							//0没有访问，1正在访问，2访问过
	
	void init(int n) {
		th(n);
		lenT = 0;	memset(ET, 255, sizeof(ET));
		lenQ = 0;	memset(EQ, 255, sizeof(EQ));
	}
	void addEdge(int a, int b, int v) {
		bufT[lenT].init(b, ET[a]);	V[lenT]=v;	ET[a] = lenT ++;
		bufT[lenT].init(a, ET[b]);	V[lenT]=v;	ET[b] = lenT ++;
	}
	void addQuery(int a, int b) {
		bufQ[lenQ].init(b, EQ[a]);				EQ[a] = lenQ ++;
		bufQ[lenQ].init(a, EQ[b]);				EQ[b] = lenQ ++;
	}
	//1.【递归版】
	void dfs(int a) {
		vis[a] = 1;
		
		for(int i = ET[a]; i != -1; i = bufT[i].nxt) {
			if(vis[bufT[i].b])	continue;
			route[bufT[i].b] = route[a] + V[i];	//update route!
			dfs(bufT[i].b);
			unio(a, bufT[i].b);
		}
		vis[a] = 2;
		for(int i = EQ[a]; i != -1; i = bufQ[i].nxt) {
			if(vis[bufQ[i].b] == 2) {
				ans[i/2] = find(bufQ[i].b);		// i/2 is the real order!
			}
		}
	}
	void solve(int root) {
		route[root] = 0;						//update route!
		make();
		memset(vis, 0, sizeof(vis));
		dfs(root);
	}
	//2.【非递归版】
	
	/*void solve(int root) {
		static Nod stk[maxn];
		make();
		memset(vis, 0, sizeof(vis));
		vis[root] = 1;
		
		stk[0].init(root, ET[root]);
		int len = 1;
		route[root] = 0;						//update route!
		
		while(1) {
			Nod & cur = stk[len-1];//here, b means current Nod, nxt means nxt's pointer(as buf.nxt)!
			if(cur.nxt == -1) {
				vis[cur.b] = 2;
				for(int i = EQ[cur.b]; i != -1; i = bufQ[i].nxt) {
					if(vis[bufQ[i].b] == 2) {
						ans[i/2] = find(bufQ[i].b);
					}
				}
				if(--len == 0)	break;
				unio(stk[len-1].b, cur.b);	//stk[stkLen-1].b = cur's father!
			} else {
				int & i = cur.nxt;
				if(!vis[bufT[i].b]) {
					vis[bufT[i].b] = 1;
					route[bufT[i].b] = route[cur.b] + V[i];//update route!
					stk[len ++].init(bufT[i].b, ET[bufT[i].b]);
				}
				i = bufT[i].nxt;
			}
		}
	}*/
} tar;

