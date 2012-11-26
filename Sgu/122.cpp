/*
 * Author: Yang Zhang
 * Created Time: Thu 16 Aug 2012 07:46:33 PM UTC
 * File Name: 122.cpp
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
#define maxn 1005
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

int n;
bool g[maxn][maxn];
int arr[maxn];
int main() {
	memset(g, 0, sizeof(g));
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		string input;
		getline(cin, input);
		istringstream iss;
		iss.str(input);
		int x;
		while (iss >> x) {
			g[i][x - 1] = g[x - 1][i] = 1;
		}
	}
	dirac(g, n, arr);
	int k;
	for (int i = 0; i < n; i++)
		if (arr[i] == 0) {
			k = i;
			break;
		}
	for (int i = k; i < n; i++)
		printf("%d ", arr[i] + 1);
	for (int i = 0; i < k; i++)
		printf("%d ", arr[i] + 1);
	printf("1\n");
	return 0;
}
