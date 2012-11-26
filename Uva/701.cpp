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

int x;

double log2(double n)
{
	return log(n) / log(2);
}

int main()
{
	freopen("a", "r", stdin);
	while (cin >> x)
	{
		bool find = false;
		for (int i = (int)log10(x) + 2; !find; i++)
		{
			double A = log2(x) + i * log2(10);
			double B = log2(x + 1) + i * log2(10);
			for (int j = (int)A; j < B && !find; j++)
			if (j >= A && j < B)
			{
				cout << j << endl;
				find = true;
			}
		}
	}
	return 0;
}
