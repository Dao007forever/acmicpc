#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	freopen("a", "r", stdin);
	int n, diff, x, y, res;
	cin >> n;
	while (n--)
	{
		cin >> x >> y;
		diff = x - y;
		if (diff == 0 || diff == 2)
		{
			res = diff + 4 * (y / 2) + y % 2;
			cout << res << endl;
		}
		else
		{
			cout << "No Number" << endl;
		}
	}
	return 0;
}
