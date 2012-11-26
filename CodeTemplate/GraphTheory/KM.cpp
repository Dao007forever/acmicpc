//KM_General:O(N^4)
struct KM {
	int E[MAXN][MAXN], n;		//图的所在，需传入
	bool map[MAXN][MAXN];		//每次二分匹配时的图
	
	bool visx[MAXN], visy[MAXN];//判断二分匹配时,某点是否在交错树上
	int mate[MAXN];				//V2中某点的伙伴，-1为空
	
	bool dfs(int idx) {
		visx[idx] = true;
		for(int i = 0; i < n; i ++) {
			if(map[idx][i] && !visy[i]) {
				visy[i] = true;
				if(mate[i]==-1 || dfs(mate[i])) {
					mate[i] = idx;
					return true;
				}
			}
		}
		return false;
	}
	int solve() {
		static int lx[MAXN], ly[MAXN];//V1和V2中点的标号
		int i, j;
		for(i = 0; i < n; i ++) {
			ly[i] = 0;
			lx[i] = -inf;
			for(j = 0; j < n; j ++) {
				lx[i] = max(lx[i], E[i][j]);
			}
		}
		while(true) {
			for(i = 0; i < n; i ++) {
				for(j = 0; j < n; j ++) {
					map[i][j] = lx[i]+ly[j]==E[i][j];
				}
			}
			//构图完毕，开始二分匹配
			memset(mate, 255, sizeof(mate));
			for(i = 0; i < n; i ++) {
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if(false == dfs(i))	break;
			}
			if(i == n) {	//找到完备匹配
				break;
			} else {		//未找到完备匹配，修改标号
				int ex = inf;
				for(i = 0; i < n; i ++) {
					if(false == visx[i])	continue;
					for(j = 0; j < n; j ++) {
						if(false == visy[j])
							ex = min(ex, lx[i]+ly[j]-E[i][j]);
					}
				}
				for(i = 0; i < n; i ++) {
					if(visx[i])	lx[i] -= ex;
					if(visy[i])	ly[i] += ex;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++) {
			ans += E[mate[i]][i];
		}
		return ans;
	}
}km;
/*
 *在此处要做的工作 :
 *读取二分图每两点间边的权并保存在E[][]中,
 *若X与Y数目不等，应添加配合的顶点
 *保存二分图中X与Y的顶点数n,若上一步不等应保
 *存添加顶点完毕后的n
 */

//KM_Slack:O(n^3)
struct KM {
	int E[maxn][maxn], n;		//图的所在，需传入
	int lx[maxn],ly[maxn],xmate[maxn],ymate[maxn];//标号,伙伴
	bool xvis[maxn], yvis[maxn];	//访问过
	int slack[maxn], prev[maxn];	//松弛量,Y中的点的前驱(在X中)
	queue<int> q;				//bfs时的队列
	bool bfs() {
		while(!q.empty()) {
			int p = q.front(), u = p>>1;	q.pop();
			if(p&1) {	//右面节点
				if(ymate[u] == -1){//找到,开始更新路径上的mate,返回
					while(u != -1) {
						ymate[u] = prev[u];
						swap(xmate[prev[u]], u);
					}
					return true;
				} else {	//没找到, 从ymate[u]继续找
					q.push(ymate[u]<<1); xvis[ymate[u]] = true;
				}
			} else {	//左面节点
				for(int i = 0; i < n; i++) {
					if(yvis[i]) continue;
					if(lx[u]+ly[i] == E[u][i]) {//有路径,继续找
						prev[i] = u;
						q.push((i<<1)|1);	yvis[i] = true;
					} else {				//没路径,开始松弛
						int ex = lx[u]+ly[i]-E[u][i];
						if(slack[i] > ex) {
							slack[i] = ex;
							prev[i] = u;
						}
					}
				}
			}
		}
		return false;
	}
	int solve() {
		for(int i = 0; i < n; i ++) {
			ly[i] = 0;
			lx[i] = *max_element(E[i], E[i]+n);
		}
		memset(xmate, 255, sizeof(xmate));
		memset(ymate, 255, sizeof(ymate));
		bool agu = true;
		for(int idx = 0; idx < n; idx += agu) {
			if(agu) {
				memset(xvis, 0, sizeof(xvis));
				memset(yvis, 0, sizeof(yvis));
				memset(slack, 63, sizeof(slack));
				while(!q.empty()) q.pop();
				q.push(idx<<1);	xvis[idx] = true;
			}
			if(agu = bfs())	continue;	//找到一条增广, 进行下一点
			int ex = inf;
			for(int i = 0; i < n; i++)
				if(!yvis[i])	ex = min(ex, slack[i]);
			for(int i = 0; i < n; i++) {
				if(xvis[i]) lx[i] -= ex;
				if(yvis[i]) ly[i] += ex;
				slack[i] -= ex;
				if(!yvis[i] && slack[i] == 0) {
					q.push((i<<1)|1);	yvis[i] = true;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++)
			ans += E[i][xmate[i]];
		return ans;
	}
}km;
