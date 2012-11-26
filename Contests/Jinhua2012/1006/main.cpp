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

int main(int argc, char const *argv[])
{
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		vector<int> nxt(n + 1, -1);
		vector<double> E(n + 1);
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			nxt[a] = b;
		}
		E[n] = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (nxt[i] != -1) {
				E[i] = E[nxt[i]];
			} else {
				for (int k = 1; k <= 6; k++)
					E[i] += E[min(n, i + k)] / 6;
				E[i] += 1.0;
			}
		}
		printf("%.4f\n", E[0]);
	}
	return 0;
}