#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	freopen("a", "r", stdin);
	string c[10], s, t;
	cin >> s;
	for (int i = 0; i < 10; i++)
		cin >> c[i];
	for (int i = 0; i < 8; i++)
	{
		t = s.substr(i * 10, 10);
		for (int j = 0; j < 10; j++)
			if (c[j] == t) cout << j;
	}
	cout << endl;
	return 0;
}
