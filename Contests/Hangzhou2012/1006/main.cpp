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

int n, m;

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		int sum = 0, Min = 0x3f3f3f3f, num = 0;
		vector<int> p;
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (b >= 1) {
				sum += b; num++;
				Min = min(Min, b);
			}
			else p.PB(a);
		}
		if (Min <= m) {
			num -= Min;
		}
	}
	return 0;
}