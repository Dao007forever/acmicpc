/*
 * Author: Yang Zhang
 * Created Time: Thu 16 Aug 2012 07:42:20 PM UTC
 * File Name: 4337.cpp
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
#define maxn 410

//path is the final hamiltion path
void dirac(bool g[maxn][maxn], int n, int *path) {
	static int nxt[maxn];
	static bool vis[maxn];
	memset(nxt, 255, sizeof(nxt));
	memset(vis, 0, sizeof(vis));

	int S = 0, T;
	for (T = 1; !g[S][T]; T++);

	nxt[S] = T;
	nxt[T] = S;
	vis[S] = vis[T] = 1;

	for (int num = 2; num != n; ) {
//Step 1:
		while (1) {
			bool ok = true;
			for (int i = 0; i < n; i++) {
				if (vis[i]) continue;
				if (g[i][S]) {
					vis[i] = 1, nxt[i] = S, S = i, ok = false, num++;
				} else if (g[T][i]) {
					vis[i] = 1, nxt[T] = i, T = i, ok = false, num++;
				}
			}
			if (ok) break;
		}
		nxt[T] = S; //fix the circuit!
//Step 2,3:
		if (!g[S][T]) {
			int tgt = -1;
			int prev = S, next;
			for (int i = nxt[S]; nxt[i] != T; i = next) {
				next = nxt[i];
				nxt[i] = prev;
				prev = i;
				if (g[S][next] && g[T][i]) {
					tgt = i;
					break;
				}
			}
			//assume tgt != -1
			nxt[S] = next;
			nxt[T] = tgt;
			S = tgt;
		}
		//now S->T is a circuit
//Step 4:
		if (num == n) break;
		for (int i = 0; i < n; i++) {
			if (vis[i]) continue;
			int j = S;
			do {
				if (g[i][j]) {
					T = j;
					S = nxt[j];
					goto out;
				}
			} while ((j=nxt[j]) != S);
		}
		out:;
	}
	int len = 0, i = S;
	do {
		path[len++] = i;
	} while ((i=nxt[i]) != S);
	//assume len = n;
}

bool g[maxn][maxn];
int n, arr[maxn];
int main() {
	int m, a, b;
	while (~scanf("%d%d", &n, &m)) {
		memset(g, 0, sizeof(g));
		while (m--) {
			scanf("%d%d", &a, &b);
			g[a - 1][b - 1] = g[b - 1][a - 1] = 1;
		}
		dirac(g, n, arr);
		bool first = true;
		for (int i = 0; i < n; i++) {
			if (!first) printf(" ");
			first = false;
			printf("%d", arr[i] + 1);
		}
		puts("");
	}
}
