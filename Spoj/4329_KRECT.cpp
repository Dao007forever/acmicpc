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

int N, M, K;
char b[111][111];
int p[111], s[111];
int cnt[1 << 16];

int main() {
	freopen("in", "r", stdin);
	for (int i = 0; i < (1 << 16); i++)
		for (int j = 0; j < 16; j++)
			cnt[i] += (i & (1 << j)) > 0;
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= N; i++)
		scanf("%s", b[i] + 1);
	int ret = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			s[i - 1] = 0;
			for (int k = i; k <= N; k++)
				p[k] = 0;
			for (int l = j; l <= M; l++) {
				for (int k = i; k <= N; k++) {
					int tmp = b[k][l] - 'A';
					if ((p[k] & (1 << tmp)) == 0) 
						p[k] |= (1 << tmp);
					s[k] = s[k - 1] | p[k];
					ret += (cnt[s[k] >> 16] + cnt[s[k] & ((1 << 16) - 1)]) == K;
				}
			}
		}
	printf("%d\n", ret);
	return 0;
}
