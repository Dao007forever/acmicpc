/*
 * 一颗树，0号节点是伐木场，还可以建立K个伐木场，求点到最近的伐木场的距离*点包含的木材数的最小值。
 * 树形DP，转成左儿子又兄弟。定义状态F[I,J,K]代表在以I为根的子树里放J个伐木场，离I最近的伐木场是K。所以，F[I,J,K]:=Min{F[Lch,P,I]+F[Rch,J-P-1,K] , F[Lch,P,K]+F[Rch,J-P,K]+Cost[I,K]}。
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

const int inf = 1000000000;
struct Node {
	int w, d, lch, rch, tot, len;
}tree[111];
int f[111][55][111];
int N, K;

int dfs(int x, int fa)
{
	if (x == 0) return 0;
	if (tree[fa].lch == x) tree[x].len = tree[x].d + tree[fa].len;
	else tree[x].len = tree[fa].len - tree[fa].d + tree[x].d;
	tree[x].tot = dfs(tree[x].lch, x) + dfs(tree[x].rch, x) + 1;
	return tree[x].tot;
}

int treeDP(int x, int m, int pre)
{
	if (x == 0) return 0;
	if (f[x][m][pre] != -1) return f[x][m][pre];
	int Min = inf, t1 = inf, t2 = inf;
	for (int i = 0; i <= m; i++) {
		if (tree[tree[x].lch].tot >= i && tree[tree[x].rch].tot >= m - i - 1 && i != m)
			t1 = treeDP(tree[x].lch, i, x) + treeDP(tree[x].rch, m - i - 1, pre);
		if (t1 != inf) Min = min(Min, t1);
		if (tree[tree[x].lch].tot >= i && tree[tree[x].rch].tot >= m - i)
			t2 = treeDP(tree[x].lch, i, pre) + treeDP(tree[x].rch, m - i, pre) + tree[x].w * (tree[x].len - tree[pre].len);
		if (t2 != inf) Min = min(Min, t2);
	}
	return f[x][m][pre] = Min;
}

int main()
{
//	freopen("in", "r", stdin);
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		int w, v, d;
		cin >> w >> v >> d;
		tree[i].w = w; tree[i].d = d;
		if (!tree[v].lch) tree[v].lch = i;
		else {
			tree[i].rch = tree[v].lch;
			tree[v].lch = i;
		}
	}

	tree[0].tot = dfs(tree[0].lch, 0) + 1;
	memset(f, -1, sizeof(f));
	int ret = treeDP(tree[0].lch, K, 0);
	cout << ret << endl;
	return 0;
}
