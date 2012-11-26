/*
 * 黑书P233
 */

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

int N, K, M;

int main() {
	freopen("in", "r", stdin);
	printf("YES\n");
	scanf("%d%d%d", &N, &K, &M);
	while (K--) {
		int n, sum = 0;
		scanf("%d", &n);
		while (n--) {
			int x;
			scanf("%d", &x);
			sum += x;
		}
		printf("%d\n", sum % (N + 1) + 1);
	}
	return 0;
}
