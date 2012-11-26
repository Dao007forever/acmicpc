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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

LL fib[111];

LL head(int n, LL a) {
	if (n == 0) return 0;
	if (n == 1) return a == 2;
	if (a <= fib[n - 1]) return head(n - 1, a);
	return head(n - 2, a - fib[n - 1]) + 1;
}

LL tail(int n, LL a) {
	if (n == 0) return 0;
	if (n == 1) return a == 1;
	if (a <= fib[n - 1]) return min(tail(n - 1, a), head(n - 1, a)) + 1 + (n - 1) / 2;
	return tail(n - 2, a - fib[n - 1]);
}

LL calc(int n, LL a, LL b) {
	if (n == 1) return 1;
	if (b <= fib[n - 1]) return calc(n - 1, a, b);
	if (a > fib[n - 1]) return calc(n - 2, a - fib[n - 1], b - fib[n - 1]);
	LL ret = min(head(n - 1, a), tail(n - 1, a)) + 1 + head(n - 2, b - fib[n - 1]);
	return ret;
}

int main(int argc, char const *argv[])
{
	int q, n;
	scanf("%d%d", &q, &n);
	fib[0] = 1;
	fib[1] = 2;
	for (int i = 2; i < 80; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	while (q--) {
		LL a, b;
		//scanf("%I64d%I64d", &a, &b);
		cin >> a >> b;
		if (a > b) swap(a, b);
		int i;
		for (i = 1; fib[i] <= b; i++);
		LL ret = calc(i, a, b);
		//printf("%I64d\n", ret);
		cout << ret << endl;
	}
	return 0;
}