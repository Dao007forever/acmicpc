//1.	求最大流用的是数组模拟的SAP
//2.	加粗部分为与SAP的不同之处
//3.	可以多次执行solve（不改变存储结构）；可以加source和sink之间的边[待]。
//4.	最终的flow值为实际流量（肯定大于low）
//5.	可以有重边，但已开始要考虑清楚，重边是共存的还是互斥的
#define th(x)	this->x = x
struct Nod {
	int b, next;
	int cap, flow, low;
	void init(int b, int low, int up, int next) {
		th(b);	th(low);	cap=up-low;	th(next);
	}
};
struct BoundFlow {
	int E[maxn], n;
	int h[maxn], vh[maxn], source, sink;
	Nod buf[maxm];	int len;	//资源所在
	int lowSumIn[maxn], lowSumOut[maxn];
	void init(int n) {
		this->n = n;
		len = 0;
		memset(E, 255, sizeof(E));
		memset(lowSumIn, 0, sizeof(lowSumIn));
		memset(lowSumOut,0, sizeof(lowSumOut));
	}
	void addCap(int i, int j, int low, int up) {
		buf[len].init(j, low, up, E[i]);
		E[i] = len++;
		buf[len].init(i, 0, 0, E[j]);
		E[j] = len++;
		lowSumIn[j] += low;
		lowSumOut[i] += low;
	}
	void popCap(int i, int j) {
		E[j] = buf[E[j]].next;
		E[i] = buf[E[i]].next;
		len -= 2;
	}
	int sap(const int idx, const int maxCap) {
		if(idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for(int i = E[idx]; i != -1; i = buf[i].next) {
			Nod & nod = buf[i];
			if(nod.cap-nod.flow > 0) {
				if(h[idx]==h[nod.b]+1) {
					d = sap(nod.b, min(l, nod.cap-nod.flow));
					nod.flow += d;
					buf[i ^ 1].flow -= d;//i^1是i的伙伴
					l -= d;
					if(h[source]==n||l==0) return maxCap-l;
				}
				minH=min(minH, h[nod.b]+1);
			}
		}
		if(l == maxCap) {
			vh[h[idx]] --;
			vh[minH] ++;
			if(vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	int solveSAP(int source, int sink) {
		if(source == sink)	return inf;
		th(source);	th(sink);
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		//for(int i = 0; i < len; i ++)	buf[i].flow = 0;//去掉
		int ans = 0;
		while(h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
	int solve(int source, int sink) {			//主程序开始
		int total = 0;
		for(int i = 0; i < n; i ++) {			//添加①
			addCap(i, n+1, 0, lowSumOut[i]);
			addCap(n, i, 0, lowSumIn[i]);
			total += lowSumIn[i];
		}
		n += 2;									//添加②
		addCap(sink, source, 0, inf);			//添加③
		for(int i = 0; i < len; i ++)	buf[i].flow = 0;
		int ans = solveSAP(n-2, n-1);			//***求解可行流
		popCap(sink, source);					//恢复③
		n -= 2;									//恢复②
		for(int i = n-1; i >= 0; i --) {		//恢复①
			popCap(n, i);
			popCap(i, n+1);
		}
		if(total != ans)	return -1;			//无可行流，返回
		solveSAP(source, sink);					//求最大流
//如果要求可行流，去掉此句。如果要求最小流，二分枚举sink到source的下界
		ans = 0;
		for(int i = 0; i < len; i ++) {
			buf[i].flow += buf[i].low;			//附加上low流量
			if(buf[i].b==sink)	ans += buf[i].flow;//统计流量
		}
		return ans;
	}
};

//sgu 194，求无源汇的可行流
BoundFlow bf;

int main()
{
	freopen("a.txt", "r", stdin);
	int N, M;
	scanf("%d%d", &N, &M);
	bf.init(N + 2);
	for (int i = 1; i <= M; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		bf.addCap(a, b, c, d);
	}
	bf.solve(0, N + 1);
	return 0;
}

//sgu 176，求最小流，枚举源点到汇点的流量下界
BoundFlow bf;

int main()
{
	freopen("a.txt", "r", stdin);
	int N, M;
	scanf("%d%d", &N, &M);
	bf.init(N);
	for (int i = 1; i <= M; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (d == 0) bf.addCap(a, b, 0, c);
		else bf.addCap(a, b, c, c);
	}
	if (!bf.solve(1, N))
	{
		printf("Impossible\n");
	}
	else
	{
		int Left = -1, Right = 1000000, Mid;
		bf.init(N + 2);
		while (Left <= Right)
		{
			Mid = (Left + Right) / 2;
			bf.addCap(1, N, Mid, inf);
			if (bf.solve(0, N + 1)) Right = Mid - 1;
			else Left = Mid + 1;
		}
		printf("%d\n", Right + 1);
		bf.print(0, N + 1);
	}
	return 0;
}