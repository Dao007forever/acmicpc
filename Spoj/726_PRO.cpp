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
multiset<int> myset;
multiset<int>::iterator it, it1, it2;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int k, x;
		scanf("%d", &k);
		while (k--)
		{
			scanf("%d", &x);
			myset.insert(x);
		}
		/*for (it = myset.begin(); it != myset.end(); it++)
			cout << *it << " ";
		cout << endl;*/
		it1 = myset.begin(); 
		it2 = myset.end();
		it2--;
		int tmp = *it2 - *it1;
		//cout << tmp << endl;
		ans += (long long)tmp;
		myset.erase(it1);
		myset.erase(it2);
	}
	cout << ans << endl;
	return 0;
}
