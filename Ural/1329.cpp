/*
 * 给一棵树，有一些询问a，b，问b是否在a为根的子树或者a是否在b为根的子树中或者都不是
 * Tarjan算法求离线LCA
 */
#pragma comment(linker, "/STACK:16777216")
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 40005
struct node {
	int v, id, next;
}edge[2 * MAXN], qedge[2 * MAXN];
int p[MAXN], Rank[MAXN], visit[MAXN];
int res[MAXN][3];
int N, Q;
int qnum, qHead[MAXN];
int num, Head[MAXN];

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void qaddEdge(int u, int v, int w) {
	qedge[qnum].v = v;
	qedge[qnum].id = w;
	qedge[qnum].next = qHead[u];
	qHead[u] = qnum++;
}

int Find_Set(int x)
{
	if (x != p[x])
		p[x] = Find_Set(p[x]);
	return p[x];
}

void Tarjan(int u, int fa)
{
	p[u] = u;
	for (int i = Head[u]; i != -1; i = edge[i].next) {
		if (edge[i].v != fa) {
			Tarjan(edge[i].v, u);
			p[edge[i].v] = u;
		}
	}
	visit[u] = 1;
	for (int i = qHead[u]; i != -1; i = qedge[i].next) {
		if (visit[qedge[i].v]) {
			int tmp = Find_Set(qedge[i].v);
			res[qedge[i].id][2] = tmp;
		}
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	num = qnum = 0;
	memset(Head, -1, sizeof(Head));
	memset(qHead, -1, sizeof(qHead));
	cin >> N;
	for (int i = 0; i < N; i++) {
		int u, v;
		cin >> u >> v;
		if (v == -1) v = 40001;
		if (u == -1) u = 40001;
		addEdge(u, v);
		addEdge(v, u);
	}
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int u, v;
		cin >> u >> v;
		if (v == -1) v = 40001;
		if (u == -1) u = 40001;
		res[i][0] = u;
		res[i][1] = v;
		qaddEdge(u, v, i);
		qaddEdge(v, u, i);
	}
	Tarjan(40001, -1);
	for (int i = 0; i < Q; i++) {
		if (res[i][2] == res[i][0]) printf("1\n");
		else if (res[i][2] == res[i][1]) printf("2\n");
		else printf("0\n");
	}
	return 0;
}
