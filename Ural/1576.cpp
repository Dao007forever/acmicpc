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

int N1, C1, N2, T, C2, N3, K;
int r1, r2;

int main() {
	cin >> N1 >> C1;
	cin >> N2 >> T >> C2;
	cin >> N3;
	cin >> K;
	int tot = 0, m = 0;
	while (K--) {
		int x, y, t = 0;
		scanf("%d:%d", &x, &y);
		t = x * 60 + y;
		if (t > 6)
			m += (t / 60 + (t % 60 > 0));
	}
	printf("Basic:     %d\n", N1 + C1 * m);
	m -= T;
	if (m <= 0) printf("Combined:  %d\n", N2);
	else printf("Combined:  %d\n", N2 + C2 * m);
	printf("Unlimited: %d\n", N3);
	return 0;
}
