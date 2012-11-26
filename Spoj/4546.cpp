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

const int MAXN = 362880 + 10;
const int INF = 100;
const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
char st[20];
int s[9];
int dis[MAXN], pre[MAXN];

int Cantor(int s[])
{
	int num = 0;
	for (int i = 0; i < 9; i++)
	{
		int temp = 0;
		for (int j = i + 1; j < 9; j++)
		{
			if (s[j] < s[i]) temp++;
		}
		num += fac[9 - i -1] * temp;
	}
	return (num + 1);
}

void Uncantor(int x)
{
	x--;
	bool h[12] = {0};
	for (int i = 0; i < 9; i++)
	{
		int t = x / fac[9 - i - 1];
		x -= t * fac[9 - i - 1];
		int j, l;
		for (j = 1, l = 0; l <= t; j++)
			if (!h[j]) l++;
		j--;
		h[j] = true;
		s[i] = j;
	}
}

queue<int> Q;
void BFS()
{
	memset(s, 0, sizeof(s));
	for (int i = 0; i <= 362880; i++)
		dis[i] = INF;
	for (int i = 0; i < 9; i++)
		s[i] = i + 1;
	int s0 = Cantor(s), x, temp;
	dis[s0] = 0;
	pre[s0] = -1;
	Q.push(s0);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if (dis[u] == 9) break;
		
		Uncantor(u);
		temp = s[0]; s[0] = s[3]; s[3] = s[4]; s[4] = s[1]; s[1] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1) 
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[0]; s[0] = s[1]; s[1] = s[4]; s[4] = s[3]; s[3] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[1]; s[1] = s[4]; s[4] = s[5]; s[5] = s[2]; s[2] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[1]; s[1] = s[2]; s[2] = s[5]; s[5] = s[4]; s[4] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[3]; s[3] = s[6]; s[6] = s[7]; s[7] = s[4]; s[4] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[3]; s[3] = s[4]; s[4] = s[7]; s[7] = s[6]; s[6] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[4]; s[4] = s[7]; s[7] = s[8]; s[8] = s[5]; s[5] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1;
//			pre[x] = u;
			Q.push(x);
		}

		Uncantor(u);
		temp = s[4]; s[4] = s[5]; s[5] = s[8]; s[8] = s[7]; s[7] = temp;
		x = Cantor(s);
		if (dis[x] > dis[u] + 1)
		{
			dis[x] = dis[u] + 1; 
//			pre[x] = u;
			Q.push(x);
		}
	}
}

void Print(int x)
{
	if (pre[x] != -1)
		Print(pre[x]);
	Uncantor(x);
	for (int i = 0; i < 9; i++)
		printf("%d", s[i]);
	printf("\n");
}

int main()
{
	freopen("a.txt", "r", stdin);
	BFS();
	int test = 0;
	while (scanf("%s", st) != EOF)
	{
		test++;
		if (strcmp(st, "0000000000") == 0) break;
		char num[3] = "";
		num[0] = st[0];
		int N = atoi(num);
		memset(s, 0, sizeof(s));
		for (int i = 0; i < 9; i++)
			s[i] = st[i + 1] - '0';
		int res = dis[Cantor(s)];
		if (res <= N) printf("%d. %d\n", test, res);
		else printf("%d. -1\n", test);
//		Print(Cantor(s));
	}
	return 0;
}
