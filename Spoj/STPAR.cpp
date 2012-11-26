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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

const int MAXN = 1000 + 10;
int N;
int order[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while(scanf("%d", &N) != EOF && N)
	{
		int need = 1, i;
		bool state = true;
		stack<int> St;
		while (!St.empty())
			St.pop();
		REP(i, N)
		{
			scanf("%d", order + i);
		}
		REP(i, N)
		{
			while (!St.empty() && St.top() == need)
			{
				need++;
				St.pop();
			}
			if (order[i] == need)
			{
				need++;
			}else if (!St.empty() && St.top() < order[i])
			{
				state = false;
				break;
			}
			else
			{
				St.push(order[i]);
			}
		}
		if (state) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}

