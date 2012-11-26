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

struct Node
{
	int time, event;
}data[11111];
int N;

bool cmp(const Node &x, const Node &y)
{
	if (x.time < y.time) return 1;
	if (x.time > y.time) return 0;
	if (x.event < y.event) return 1;
	if (x.event > y.event) return 0;
	return 0;
}

int main()
{
	freopen("a", "r", stdin);
	int Test = 10;
	while (Test--)
	{
		int a, b;
		scanf("%d%d%d", &a, &b, &N);
		int p = 0;
		data[p].time = a;
		data[p++].event = 0;
		data[p].time = b;
		data[p++].event = 1;
		for (int i = 0; i < N; i++)
		{
			scanf("%d%d", &a, &b);
			data[p].time = a;
			data[p++].event = -1;
			data[p].time = b;
			data[p++].event = 2;
		}
		sort(data, data + p, cmp);

		int Min = 2147483647, Max = 0;
		a = 0, b = 0;
		for (int i = 0; i < p; i++)
		{
			switch(data[i].event)
			{
				case -1:
					a++;
					if (b)
					{
						if (a < Min) Min = a;
						if (a > Max) Max = a;
					}
					break;
				case 0:
					b = 1;
					if (a < Min) Min = a;
					if (a > Max) Max = a;
					break;
				case 1:
					b = 0;
					break;
				case 2:
					a--;
					if (b)
					{
						if (a < Min) Min = a;
						if (a > Max) Max = a;
					}
					break;
			};
		}
		printf("%d %d\n", Min, Max);
	}
	return 0;
}
