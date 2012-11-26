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

int N;
int A[3][3], B[3][3];
bool Find;

bool Check(int x, int y)
{
	int cnt = 0;
	if (x && A[x - 1][y] > A[x][y]) cnt++;
	if (x < N - 1 && A[x + 1][y] > A[x][y]) cnt++;
	if (y && A[x][y - 1] > A[x][y]) cnt++;
	if (y < N - 1 && A[x][y + 1] > A[x][y]) cnt++;
	return (cnt == B[x][y]);
}

void DFS(int x, int y)
{
	if (y == N)
	{
		x++;
		y = 0;
	}
	if (x == N)
	{
		for (int i = 0; i < N; i++)
			if (!Check(N - 1, i)) return;
		for (int i = 0; i < N; i++)
		{
			printf("%d", A[i][0]);
			for (int j = 1; j < N; j++)
				printf(" %d", A[i][j]);
			printf("\n");
		}
		exit(0);
	}
	for (int i = 0; i < 10; i++)
	{
		A[x][y] = i;
		if (!x || Check(x - 1, y)) DFS(x, y + 1);
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		scanf("%d", &B[i][j]);
	DFS(0, 0);
	printf("NO SOLUTION\n");
	return 0;
}
