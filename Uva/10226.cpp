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

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d\n", &Test);
	string name;
	bool blank = false;
	while (Test--)
	{
		if (blank) puts("");
		blank = true;
		int n = 0;
		map<string, int> mymap;
		while (getline(cin, name) && name.size() > 0)
		{
			mymap[name]++;
			n++;
		}
		for (map<string, int>::iterator it = mymap.begin(); it != mymap.end(); it++)
		{
			double ans = (double)mymap[it->first] * 100.0 / n;
			cout << it->first << " ";
			printf("%.4lf\n", ans);
		}
	}
	return 0;
}
