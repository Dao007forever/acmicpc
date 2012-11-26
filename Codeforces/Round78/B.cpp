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

const int MAXN = 1000 + 10;
int N;
int p[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	int sum = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &p[i]);
		sum += p[i];
	}
	if (sum % N != 0)
	{
		printf("Unrecoverable configuration.");
	}
	else
	{
		int ave = sum / N, tot = 0;
		int t1 = 0, t2 = 0;
		bool flag = true;
		for (int i = 1; i <= N; i++)
		{
			if (p[i] == ave) tot++;
			else if (p[i] < ave) t1 = i;
			else if (p[i] > ave) t2 = i;
		}
		if (tot == N)
		{
			printf("Exemplary pages.");
		}
		else if (tot == N - 2 && ave - p[t1] == p[t2] - ave)
		{
			int del = ave - p[t1];
			printf("%d ml. from cup #%d to cup #%d.", del, t1, t2);
		}
		else printf("Unrecoverable configuration.");
	}
	return 0;
}
