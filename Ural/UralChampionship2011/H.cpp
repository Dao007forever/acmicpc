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

const int MAXN = 100 + 10;
const int INF = 1000000;
int N, tot;
int F[3 * MAXN][3 * MAXN];
struct Node
{
	char na[30];
	int d;
}P[3 * MAXN];

int ID(char *s)
{
	for (int i = 1; i <= tot; i++)
	if (strcmp(s, P[i].na) == 0)
	{
		return i;
	}
	strcpy(P[++tot].na, s);
	return tot;
}

bool cmp(Node a, Node b)
{
	return strcmp(a.na, b.na);
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	tot = 0;
	for (int i = 1; i <= 3 * N; i++)
	for (int j = 1; j <= 3 * N; j++)
		F[i][j] = INF;
	for (int i = 1; i <= N; i++)
	{
		char s1[30], s2[30], s3[30];
		scanf("%s%s%s", s1, s2, s3);
		int d1 = ID(s1), d2 = ID(s2), d3 = ID(s3);
		F[d1][d2] = F[d2][d1] = 1;
		F[d1][d3] = F[d3][d1] = 1;
		F[d2][d3] = F[d3][d2] = 1;
	}
	for (int k = 1; k <= tot; k++)
	for (int i = 1; i <= tot; i++)
	for (int j = 1; j <= tot; j++)
	if (i != j && j != k && i != k)
		if (F[i][k] + F[k][j] < F[i][j])
			F[i][j] = F[i][k] + F[k][j];
	char st1[30] = "Isenbaev", st2[30] = "Vladislav";
	bool find = false;
	int A;
	for (int i = 1; i <= tot; i++)
	if (strcmp(P[i].na, st1) == 0 || strcmp(P[i].na, st2) == 0)
	{
		A = i;
		find = true;
		break;
	}
	if (!find)
	{
		for (int i = 1; i <= tot; i++)
		for (int j = i + 1; j <= tot; j++)
		if (strcmp(P[j].na, P[i].na) < 0)
		{
			Node temp = P[i];
			P[i] = P[j];
			P[j] = temp;
		}
		for (int i = 1; i <= tot; i++)
		{
			printf("%s undefined\n", P[i].na);
		}
		return 0;
	}
	for (int i = 1; i <= tot; i++)
	if (i != A)
		P[i].d = F[A][i];
	for (int i = 1; i <= tot; i++)
	for (int j = i + 1; j <= tot; j++)
	if (strcmp(P[j].na, P[i].na) < 0)
	{
		Node temp = P[i];
		P[i] = P[j];
		P[j] = temp;
	}
	for (int i = 1; i <= tot; i++)
	{
		printf("%s", P[i].na);
		if (P[i].d == INF) printf(" undefined\n");
		else printf(" %d\n", P[i].d);
	}
	return 0;
}
