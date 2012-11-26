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

#define maxn 50005
int n;
LL vol;
LL dist[maxn], cost[maxn];

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%lld", &n, &vol);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &dist[i]);
		for (int i = 0; i < n; i++)
			scanf("%lld", &cost[i]);
		cost[n] = 0;

		int cur = n;
		LL ret = 0;
		while (cur > 0) {
			int best = cur - 1;
			bool find = false;
			for (int i = cur - 1; i >= 0; i--) {
				if (dist[cur] - dist[i] > vol) break;
				if (cost[i] < cost[best]) best = i;
				if (cost[i] < cost[cur]) {
					if (dist[i] + vol >= dist[n]) {
						ret += cost[i] * (dist[n] - dist[i]) - cost[cur] * (dist[n] - dist[cur]);
					} else {
						ret += cost[i] * vol - cost[cur] * (vol - (dist[cur] - dist[i]));
					}
					find = true;
					cur = i;
					break;
				}
			}
			if (!find) {
				ret += (LL)cost[best] * (dist[cur] - dist[best]);
				cur = best;
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}