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

int N, M, K;
int mat[222][222], sum[222][222], s[222];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d: ", cas);
		memset(sum, 0, sizeof(sum));
		memset(s, 0, sizeof(s));
		scanf("%d%d%d", &N, &M, &K);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf("%d", &mat[i][j]);
				sum[i][j] = sum[i][j - 1] + mat[i][j];
			}
		}

		int ret = 0;
		for (int c1 = 1; c1 <= M; c1++) {
			for (int c2 = c1; c2 <= M; c2++) {
				int cnt = 0;
				s[0] = 0;
				for (int i = 1; i <= N; i++)
					s[i] = s[i - 1] + sum[i][c2] - sum[i][c1 - 1];

				int l = 1, r = 1;
				for (; l <= N; l++) {
					while (s[r] - s[l - 1] < K && r <= N) {
						r++;
					}
					if (r <= N && s[r] - s[l - 1] >= K) {
						cnt += N - r + 1;
					}
				}
				ret += cnt;
			}
		}
		int S = N * (N + 1) / 2 * (M * (M + 1) / 2);
		int g = gcd(ret, S);
		ret /= g; S /= g;
		printf("%d/%d\n", ret, S);
	}
	return 0;
}