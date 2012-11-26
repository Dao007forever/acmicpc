/*
* Edge list
*/
#define th(x) this->x = x
const int MAXN = 20000 + 10;
const int MAXM = 200000 + 10;
const int inf = 0x3f3f3f3f;
struct Nod
{
	int b, next;
	int cap, flow;
	void init(int b, int cap, int next)
	{
		th(b);
		th(cap);
		th(next);
	}
};
struct SAP
{
	int E[MAXN], n;
	int h[MAXN], vh[MAXN], source, sink;
	Nod buf[MAXM * 4]; int len;
	void init(int n)
	{
		this->n = n;
		len = 0;
		memset(E, 255, sizeof(E));
	}
	void addCap(int i, int j, int cap1, int cap2 = 0)
	{
		buf[len].init(j, cap1, E[i]);
		E[i] = len++;
		buf[len].init(i, cap2, E[j]);
		E[j] = len++;
	}
	int sap(const int idx, const int maxCap)
	{
		if (idx == sink)
				return maxCap;
		int l = maxCap, d, minH = n;
		for (int i = E[idx]; i != -1; i = buf[i].next)
		{
				Nod & nod = buf[i];
				if (nod.cap-nod.flow > 0)
				{
						if (h[idx] == h[nod.b] + 1)
						{
								d = sap(nod.b, min(l, nod.cap - nod.flow));
								nod.flow += d;
								buf[i ^ 1].flow -= d;
								l -= d;
								if (h[source] == n || l == 0) return maxCap - l;
						}
						minH = min(minH, h[nod.b] + 1);
				}
		}
		if (l == maxCap)
		{
				vh[h[idx]]--;
				vh[minH]++;
				if (vh[h[idx]] == 0)
						h[source] = n;
				h[idx] = minH;
		}
		return maxCap - l;
	}
	int solve(int source, int sink)
	{
		if (source == sink) return inf;
		th(source); th(sink);
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		for (int i = 0; i < len; i++)
				buf[i].flow = 0;
		int ans = 0;
		while (h[source] != n)
				ans += sap(source, inf);
		return ans;
	}
};

/*
* Adjacency matrix
*/
const int MAXN = 100 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
	int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
	int n;
	int h[MAXN], vh[MAXN], source, sink;
	int mk[MAXN];
	void init(int n)
	{
		this->n = n;
		memset(cap, 0, sizeof(cap));
		memset(g, 0, sizeof(g));
		memset(mk, 0, sizeof(mk));
	}
	void addCap(int i, int j, int val)
	{
		cap[i][j] += val;
		g[i][j] = 1;
	}
	int sap(const int idx, const int maxCap)
	{
		if (idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for (int i = 0; i < n; i++)
		{
			if (cap[idx][i] - flow[idx][i] > 0)
			{
				if (h[idx] == h[i] + 1)
				{
					d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
					flow[idx][i] += d;
					flow[i][idx] -= d;
					l -= d;
					if (h[source] == n || l == 0) return maxCap - l;
				}
				minH = min(minH, h[i] + 1);
			}
		}
		if (l == maxCap)
		{
			vh[h[idx]]--;
			vh[minH]++;
			if (vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	int solve(int source, int sink)
	{
		if (source == sink) return inf;
		this->sink = sink;
		this->source = source;
		memset(flow, 0, sizeof(flow));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
	void dfs(int u)
	{
		mk[u] = 1;
		for (int i = 0; i < n; i++)
		{
			if (!mk[i] && cap[u][i] - flow[u][i] > 0) dfs(i);
		}
	}
	void output()
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (g[i][j] && cap[i][j] - flow[i][j] == 0 && mk[i] != mk[j])
					printf("%d %d\n", i + 1, j + 1);
	}
}sap;
