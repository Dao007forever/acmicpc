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
	int n, k;
	cin >> n >> k;
	int suma = k, sumb = 0;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		suma += a; sumb += b;
	}
	int ans = suma - (n + 1) * 2;
	if (ans < sumb) puts("Big Bang!");
	else printf("%d\n", ans - sumb);
	return 0;
}