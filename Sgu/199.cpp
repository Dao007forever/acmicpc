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

const int MAXN = 100000 + 10;
int N;
int idx[MAXN], pre[MAXN];
struct Person
{
	int s, b, idx;
}P[MAXN];

bool cmp(Person A, Person B)
{
	if (A.s != B.s)
	{
		return A.s < B.s;
	}
	return A.b > B.b;
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> P[i].s >> P[i].b;
		P[i].idx = i;
	}
	sort(P + 1, P + N + 1, cmp);

	int len = 1;
	idx[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (P[i].b > P[idx[len]].b)
		{
			len++;
			idx[len] = i;
			pre[i] = idx[len - 1];
			continue;
		}
		int Left = 1, Right = len;
		while (Left < Right)
		{
			int Mid = (Left + Right) >> 1;
			if (P[idx[Mid]].b < P[i].b) Left = Mid + 1;
			else Right = Mid;
		}
		idx[Left] = i;
		pre[i] = idx[Left - 1];
	}
	cout << len << endl;
	for (int i = idx[len]; i; i = pre[i])
	{
		cout << P[i].idx << " ";
	}
	cout << endl;
	return 0;
}
