#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
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

const int MAXN = 300 + 10;
const int inf = 0x3f3f3f3f;

struct SAP 
{
	int cap[MAXN][MAXN];
	int n;	
	int h[MAXN], vh[MAXN], source, sink;
	void init(int n) 
	{
		this->n = n;
		memset(cap, 0, sizeof(cap));
	}
	void addCap(int i, int j, int val) 
	{
		cap[i][j] += val;
	}
	int sap(const int idx, const int maxCap) 
	{
		if(idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for(int i = 0; i < n; i ++) 
		{
			if(cap[idx][i] > 0) 
			{
				if(h[idx]==h[i]+1) 
				{
					d = sap(i, min(l, cap[idx][i]));
					cap[idx][i] -= d;			
					cap[i][idx] += d;				  
					l -= d;						
					if(h[source]==n||l==0) return maxCap-l;
				}
				minH=min(minH, h[i]+1);	
			}
		}
		if(l == maxCap) 
		{
			vh[h[idx]] --;	
			vh[minH] ++;
			if(vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	int solve(int source, int sink) 
	{
		if(source == sink)
			return inf;
		this->sink = sink;
		this->source = source;
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while(h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
};

struct BoundFlow
{
	SAP sap;
	int upper[MAXN][MAXN], lower[MAXN][MAXN], flow[MAXN][MAXN];
	int n;
	void init(int n)
	{
		this->n = n;
		memset(lower, 0, sizeof(lower));
		memset(upper, 0, sizeof(upper));
	}
	int solve(int source, int sink)
	{
		sap.init(n + 2);
		int tot = 0;
		
		upper[sink][source] = inf;
		lower[sink][source] = 0;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (upper[i][j] < lower[i][j]) return -1;
				sap.addCap(i, j, upper[i][j] - lower[i][j]);
				sap.addCap(n, j, lower[i][j]);
				sap.addCap(i, n + 1, lower[i][j]);
				tot += lower[i][j];
			}
		}
		if (sap.solve(n, n + 1) != tot) return -1;
		sap.solve(source, sink);
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			flow[i][j] = upper[i][j] - sap.cap[i][j];
		tot = 0;
		for (int i = 0; i < n; i++)
			tot += flow[source][i];
		return tot;
	}
};

BoundFlow bf;

int T, M, N, Q;
int rowSum[MAXN], colSum[MAXN];

int main()
{
	freopen("a.txt", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		bool flag = true;
		int tot1 = 0, tot2 = 0;
		scanf("%d%d", &M, &N);
		bf.init(M + N + 2);
		for (int i = 0; i < M; i++)
		{
			scanf("%d", &rowSum[i]);
			tot1 += rowSum[i];
			bf.upper[M + N][i] = bf.lower[M + N][i] = rowSum[i];
		}
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &colSum[i]);
			tot2 += colSum[i];
			bf.upper[M + i][M + N + 1] = bf.lower[M + i][M + N + 1] = colSum[i];
		}
		for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{
			bf.upper[i][M + j] = inf;
			bf.lower[i][M + j] = 0;
		}
		if (tot1 != tot2) flag = false;
		scanf("%d", &Q);
		while (Q--)
		{
			int a, b, c;
			char op[10];
			scanf("%d%d%s%d", &a, &b, op, &c);
			a--; b--;
			if (a == -1 && b == -1)
			{
				for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
				{
					if (*op == '=')
						bf.upper[i][M + j] = bf.lower[i][M + j] = c;
					else if (*op == '<')
						bf.upper[i][M + j] = min(bf.upper[i][M + j], c - 1);
					else bf.lower[i][M + j] = max(bf.lower[i][M + j], c + 1);
				}
			}
			else if (a == -1)
			{
				for (int i = 0; i < M; i++)
				{
					if (*op == '=')
						bf.upper[i][M + b] = bf.lower[i][M + b] = c;
					else if (*op == '<')
						bf.upper[i][M + b] = min(bf.upper[i][M + b], c - 1);
					else bf.lower[i][M + b] = max(bf.lower[i][M + b], c + 1);
				}
			}
			else if (b == -1)
			{
				for (int j = 0; j < N; j++)
				{
					if (*op == '=')
						bf.upper[a][M + j] = bf.lower[a][M + j] = c;
					else if (*op == '<')
						bf.upper[a][M + j] = min(bf.upper[a][M + j], c - 1);
					else bf.lower[a][M + j] = max(bf.lower[a][M + j], c + 1);
				}
			}
			else
			{
				if (*op == '=')
					bf.upper[a][M + b] = bf.lower[a][M + b] = c;
				else if (*op == '<')
					bf.upper[a][M + b] = min(bf.upper[a][M + b], c - 1);
				else bf.lower[a][M + b] = max(bf.lower[a][M + b], c + 1);
			}
		}

		if (flag)
		{
			int temp = bf.solve(N + M, N + M + 1);
			if (temp == -1)
				flag = false;
		}
		if (!flag)
			printf("IMPOSSIBLE\n");
		else
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N - 1; j++)
					printf("%d ", bf.flow[i][M + j]);
				printf("%d\n", bf.flow[i][M + N - 1]);
			}
			printf("\n");
		}
	}
	return 0;
}
