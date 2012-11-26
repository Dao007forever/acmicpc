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

bool check(long long x, long long y, long long xc, long long yc)
{
	if (x == 0 && y == 0) return true;
	if (xc == 0 && yc == 0) return false;
	if (xc == 0)
	{
		if (x % yc || y % yc) return false;
		else return true;
	}
	if (yc == 0)
	{
		if (x % xc || y % xc) return false;
		else return true;
	}
	if ((x * xc + y * yc) % (xc * xc + yc * yc)) return false;
	long long tmp = (x * xc + y * yc) / (xc * xc + yc * yc);
	if ((x - tmp * xc) % yc) return false;
	else return true;
}

int main()
{
	freopen("a", "r", stdin);
	long long xa, ya, xb, yb, xc, yc;
	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	if (check(xb - xa, yb - ya, xc, yc) ||
		check(xb + xa, yb + ya, xc, yc) ||
		check(xb - ya, yb + xa, xc, yc) ||
		check(xb + ya, yb - xa, xc, yc))
		cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
