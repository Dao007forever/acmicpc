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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

int main(int argc, char const *argv[])
{
	int n, a, b;
	cin >> n >> a >> b;
	int lo = 0, hi = 0x3f3f3f3f, ret = -1;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (mid / a + mid / b >= n) {
			ret = mid;
			hi = mid - 1;
		} else lo = mid + 1;
	}
	if (ret % a == 0 && ret % b == 0) {
		printf("%d %d\n", ret / a + ret / b, ret);
	} else {
		if (ret % b == 0)swap(a, b);
		int ans = ret / a;
		ret = (ret / b + 1) * b;
		printf("%d %d\n", ans + ret / b, ret);
	}
	return 0;
}