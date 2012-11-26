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
int a[MAXN], b[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while (cin >> N && N)
	{
		for (int i = 1; i <= N; i++)
		{
			cin >> a[i];
			b[a[i]] = i;
		}
		bool flag = true;
		for (int i = 1; i < N; i++)
		if (a[i] != b[i])
		{
			flag = false;
			break;
		}
		if (flag) cout << "ambiguous" << endl;
		else cout << "not ambiguous" << endl;
	}
	return 0;
}
