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

int n;
LL a[100005];
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}
	LL sig = 1LL<<62;
	for (int Rank = 0; sig >= 1; sig >>= 1) {
		int i = Rank;
		for (; i < n && (a[i] & sig) == 0; i++);
		if (i >= n) continue;
		swap(a[Rank], a[i]);
		for (int j = 0; j < n; j++)
			if (j != Rank && (a[j] & sig) != 0) {
				a[j] ^= a[Rank];
			}
		Rank++;
	}
	LL ret = 0;
	for (int i = 0; i < n; i++)
		ret ^= a[i];
	printf("%lld\n", ret);
	return 0;
}