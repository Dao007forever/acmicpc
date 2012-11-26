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

const int MAXN = 111;
int N;
int p[MAXN];

int find(int x)
{
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	getchar();
	bool f = 0;
	while (Test--)
	{
		if (f == 1) cout << endl; f = 1;
		char ch;
		cin >> ch;
		N = ch - 'A' + 1;
		getchar();
		for (int i = 1; i <= N; i++)
			p[i] = i;
		while (1)
		{
			string s;
			getline(cin, s);
			if (s.size() == 0) break;
			int a = s[0] - 'A' + 1, b = s[1] - 'A' + 1;
			a = find(a), b = find(b);
			if (a != b) p[a] = b;
		}
		int cnt = 0;
		for (int i = 1; i <= N; i++)
		if (find(i) == i) cnt++;
		printf("%d\n", cnt);
	}
	return 0;
}
