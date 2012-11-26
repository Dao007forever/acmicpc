/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/20 14:48:37
 * File Name: 1569.cpp
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;
typedef long long F;
#define inf (1ll << 55)
#define maxV 10005
#define maxE 1000005
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, F f) {
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	bool bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return (level[t] != -1);
	}

	F dfs(int v, int t, F f) {
		if (v == t) return f;
		for (int i = used[v]; i != -1; used[v] = i = prev[i])
			if (level[to[i]] > level[v] && cap[i] > flow[i]) {
				F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}

	F solve(int s, int t) {
		while (bfs(s, t)) {
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return ans;
	}
}mf;
int N, M;
int a[105][105];
int ID(int i, int j)
{
    return i * M + j;
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &N, &M) != EOF)
    {
        LL Sum = 0;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &a[i][j]);
            Sum += (LL)a[i][j];
        }

        mf.init(N * M + 2);
        int source = N * M, sink = N * M + 1;
        for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            if (!((i + j) & 1))
            {
                mf.addCap(source, ID(i, j), a[i][j]);
                if (i - 1 >= 0)
                    mf.addCap(ID(i, j), ID(i - 1, j), inf);
                if (i + 1 < N)
                    mf.addCap(ID(i, j), ID(i + 1, j), inf);
                if (j - 1 >= 0)
                    mf.addCap(ID(i, j), ID(i, j - 1), inf);
                if (j + 1 < M)
                    mf.addCap(ID(i, j), ID(i, j + 1), inf);
            }
            else mf.addCap(ID(i, j), sink, a[i][j]);
        }
        cout << Sum - mf.solve(source, sink) << endl;
    }
    return 0;
}

