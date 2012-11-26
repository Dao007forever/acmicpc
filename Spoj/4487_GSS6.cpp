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

#define SIZE 200010
typedef int type;
const int inf = 10010;
#define key (CH[CH[r][1]][0])

int CH[SIZE][2], P[SIZE];
type V[SIZE];
int len;

int CNT[SIZE];

int SUM[SIZE];
int LL[SIZE], RR[SIZE], MM[SIZE];

int newNode()
{
	return len++;
}

void initNode(int x, type v, int ch0, int ch1, int p)
{
	V[x] = v;
	CH[x][0] = ch0;
	CH[x][1] = ch1;
	P[x] = p;

	CNT[x] = 1;

	SUM[x] = V[x];
	MM[x] = LL[x] = RR[x] = V[x];
}

void initTree()
{
	len = 1;
	initNode(0, -inf, 0, 0, 0);
	CNT[0] = SUM[0] = 0;
}

struct SplayTree
{
	int r;
	//---------------------fundamental functions-------------------
	SplayTree(type lv, type rv)
	{
		int a = newNode();
		int b = newNode();
		initNode(a, lv, 0, b, 0);
		initNode(b, rv, 0, 0, a);
		push_up(b);
		push_up(a);
		r = a;
	}

	void rotate(int x, bool c)
	{
		int y = P[x];

		CH[y][!c] = CH[x][c];
		if (CH[x][c]) P[CH[x][c]] = y;
		CH[x][c] = y;

		P[x] = P[y];
		P[y] = x;

		if (P[x]) CH[ P[x] ][ CH[P[x]][1] == y ] = x;
		else r = x;
		push_up(y);
	}

	void splay(int x, int f = 0)
	{
		int y;
		bool b1, b2;
		while ((y = P[x]) != f)
		{
			if (P[y] == f)
			{
				rotate(x, CH[y][0] == x);
			}
			else
			{
				b1 = (y == CH[P[y]][0]);
				b2 = (x == CH[y][0]);
				rotate((b1 ^ b2) ? x : y, b2);
				rotate(x, b1);
			}
		}
		push_up(x);
	}

	void select(int rank, int f = 0)
	{
		if (rank >= CNT[r] || rank < 0) return;
		int i = r;
		while (true)
		{
			if (CNT[CH[i][0]] == rank) break;
			if (CNT[CH[i][0]] > rank)
			{
				i = CH[i][0];
			}
			else
			{
				rank -= CNT[CH[i][0]] + 1;
				i = CH[i][1];
			}
		}
		splay(i, f);
	}

	void interval(int begin, int end)
	{
		select(begin - 1);
		select(end, r);
	}
	//-------------------insert and remove----------------------
	void insert(type *arr, int n)
	{
		int x = newNode();
		initNode(x, arr[n - 1], insertDfs(arr, n - 1, x), CH[r][1], r);

		if (CH[x][1]) P[CH[x][1]] = x;
		CH[r][1] = x;
		splay(x);
	}
	
	int insertDfs(type *arr, int n, int father)
	{
		if (n <= 0) return 0;
		int idx = n / 2;
		int x = newNode();
		initNode(x, arr[idx], insertDfs(arr, idx, x), insertDfs(arr + idx + 1, n - idx - 1, x), father);
		push_up(x);
		return x;
	}
	int cutKeyTree()
	{
		if (!key) return 0;
		int res = key;
		key = P[res] = 0;
		splay(CH[r][1]);
		return res;
	}
	//-------------------------push--------------------------
	void push_up(int idx)
	{
		if (!idx) return;
		CNT[idx] = CNT[CH[idx][0]] + CNT[CH[idx][1]] + 1;
		SUM[idx] = SUM[CH[idx][0]] + SUM[CH[idx][1]] + V[idx];

		LL[idx] = max(LL[CH[idx][0]], SUM[CH[idx][0]] + V[idx] + max(LL[CH[idx][1]], 0));
		RR[idx] = max(RR[CH[idx][1]], SUM[CH[idx][1]] + V[idx] + max(RR[CH[idx][0]], 0));
		MM[idx] = max(MM[CH[idx][0]], MM[CH[idx][1]]);
		MM[idx] = max(MM[idx], V[idx] + max(0, RR[CH[idx][0]]) + max(0, LL[CH[idx][1]]));
	}
	//----------------------other functions-------------------
	void replaceKeyTree(int v)
	{
		V[key] = v;
		splay(key);
	}
	void outputKeyMM()
	{
		printf("%d\n", MM[key]);
	}
};

int arr[SIZE];

int ms()
{
	char c;
	bool fu = false;
	while (c = getchar(), c > '9' || c < '0') if (c == '-') fu = true;
	int res;
	for (res = c - '0'; c = getchar(), c >= '0' && c <= '9'; res = res * 10 + c - '0');
	if (fu) res = -res;
	return res;
}

int main()
{
	freopen("in", "r", stdin);
	int n, q, a, b;
	char c;
	n = ms();
	initTree();
	SplayTree sp(0, 0);
	for (int i= 0; i < n; i++)
		arr[i] = ms();
	sp.insert(arr, n);
	q = ms();
	while (q--)
	{
		while (c = getchar(), c > 'Z' || c < 'A');
		if (c == 'I')
		{
			a = ms(); b = ms();
			sp.select(a - 1);
			sp.insert(&b, 1);
		}
		else if (c == 'D')
		{
			a = ms();
			sp.interval(a, a + 1);
			sp.cutKeyTree();
		}
		else if (c == 'R')
		{
			a = ms(); b = ms();
			sp.interval(a, a + 1);
			sp.replaceKeyTree(b);
		}
		else if (c == 'Q')
		{
			a = ms(); b = ms();
			sp.interval(a, b + 1);
			sp.outputKeyMM();
		}
		else while(1);
	}
	return 0;
}
