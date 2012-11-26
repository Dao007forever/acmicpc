/*
判断图是否是弦图

首先求完美消除序列
完美消除序列的定义:
v1,v2,...,vn
对于vi有vi在{vi,vi+1,...,vn}中与vi相连的点的诱导子图是团

弦图存在完美消除序列

方法:
首先对于每个点有label[i]=0
每次选出label最大的点标号
将至于相邻的未标号的点的label++
第i次标号的点在序列中的位置是第n-i+1位

最后check得到的序列是否是完美消除序列
自后向前,对于vi及其相邻点vi1,vi2,...,vik
判断vi1与vi2,vi3,...,vik是否相邻
*/
#define MAXN 1005
struct ChordalGraph{
	int n, m;
	int label[MAXN], que[MAXN];
	bool flag[MAXN][MAXN];
	vector<int> adj[MAXN];

	void init(int n, int m) {
		this->n = n; this->m = m;
		memset(label, 0, sizeof(label));
		memset(flag, 0, sizeof(flag));
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
		adj[v].PB(u);
		flag[u][v] = flag[v][u] = true;
	}

	void PerfectSequence() {
		for (int i = 0; i < n; i++) {
			int Max = -1;
			for (int j = 1; j <= n; j++)
				if (label[j] >= 0 && (Max == -1 || label[j] > label[Max])) {
					Max = j;
				}
			que[i] = Max;
			label[Max] = -1;
			for (int j = 0; j < adj[Max].size(); j++)
				if (label[adj[Max][j]] >= 0)
					label[adj[Max][j]]++;
		}
	}

	bool isChordalGraph() {
		PerfectSequence();
		bool ret = true;
		for (int i = 1; i < n && ret; i++) {
			int first = -1;
			for (int j = 0; j < i && ret; j++) {
				if (flag[que[i]][que[j]]) {
					if (first == -1) first = que[j];
					else ret &= flag[first][que[j]];
				}
			}
		}
		return ret;
	}
};