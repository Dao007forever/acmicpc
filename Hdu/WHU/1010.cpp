#include <cstdio>
#include <iostream>
using namespace std;

int u1, u2, u3, d1, d2, d3;

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	cin >> Test;
	for (int i = 1; i <= Test; i++) {
		printf("Case %d: ", i);
		cin >> u1 >> d1 >> u2 >> d2 >> u3 >> d3;
		int t1 = 0, t2 = 0;
		if (u1 - d1 < 0) t1++;
		else if (u1 - d1 > 0) t2++;
		if (u2 - d2 < 0) t1++;
		else if (u2 - d2) t2++;
		if (u3 - d3 < 0) t1++;
		else if (u3 - d3 > 0) t2++;

		if (t1 && t2 || (t1 == 0 && t2 == 0)) puts("Yes");
		else puts("No");
	}
	return 0;
}
