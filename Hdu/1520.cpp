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

const int MAXN = 6000 + 10;
struct Tree
{
	int father, brother, child, TakeParty, Not;
	int Max()
	{
		return TakeParty > Not ? TakeParty : Not;
	}

	void init()
	{
		father = child = brother = Not = 0;
	}
}tree[MAXN];

void DFS(int idx)
{
	int child;
	child = tree[idx].child;
	while (child)
	{
		DFS(child);
		tree[idx].TakeParty += tree[child].Not;
		tree[idx].Not += tree[child].Max();
		child = tree[child].brother;
	}
}

int main()
{
	freopen("a", "r", stdin);
	int N, a, b;
	while (scanf("%d", &N) == 1)
	{
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &tree[i].TakeParty);
			tree[i].init();
		}
		while (scanf("%d%d", &a, &b))
		{
			if (a == 0 && b == 0) break;
			tree[a].father = b;
			tree[a].brother = tree[b].child;
			tree[b].child = a;
		}
		for (int i = 1; i <= N; i++)
		if (!tree[i].father)
		{
			DFS(i);
			printf("%d\n", tree[i].Max());
			break;
		}
	}
	return 0;
}
