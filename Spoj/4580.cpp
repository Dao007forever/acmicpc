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

int n;
int A[111];
map<int,int> mp;
vector<int> v;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", A + i);
	int tot = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (A[k])
				{
					int tmp = (A[i] + A[j]) * A[k];
					v.push_back(tmp);
				}
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
		mp[v[i]] = ++tot;
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				int tmp = A[i] * A[j] + A[k];
				map<int,int>::iterator k1 = mp.upper_bound(tmp), k2 = mp.lower_bound(tmp);
				if ((*k1).second > tot)
				{
//					printf("%d\n", tot - (*k2).second + 1);
					ans += tot - (*k2).second + 1;
				}
				else 
				{
//					printf("%d\n", (*k1).second - (*k2).second + 1);
					ans += (*k1).second - (*k2).second + 1;
				}
			}
	printf("%d\n", ans);
	return 0;
}
