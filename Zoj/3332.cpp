/*
 * Author: Yang Zhang
 * Created Time: Thu 16 Aug 2012 08:53:02 PM UTC
 * File Name: 3332.cpp
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

//Hamilton path
#define maxn 105
bool g[maxn][maxn];
int n, cnt;
int arr[maxn];
void hamilton(int start) {
	static int nxt[maxn];
	memset(nxt, 255, sizeof(nxt));

	int head = start;
	for (int i = 0; i < n; i++) {
		if (i == start) continue;
		if (g[i][head]) {
			nxt[i] = head;
			head = i;
		} else {
			int prev = head;
			int iter = nxt[head];
			while (1) {
				if (iter == -1 || g[i][iter]) {
					nxt[prev] = i;
					nxt[i] = iter;
					break;
				}
				prev = iter;
				iter = nxt[iter];
			}
		}
	}
	cnt = 0;
	for (int x = head; x != -1; x = nxt[x])
		arr[cnt++] = x;
	for (int i = 0; i < n; i++) {
		if (i != 0) printf(" ");
		printf("%d", arr[i] + 1);
	}
	puts("");
}
int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(g, 0, sizeof(g));
		scanf("%d", &n);
		for (int i = 0; i < n * (n - 1) / 2; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g[a - 1][b - 1] = 1;
		}
		hamilton(0);
	}
	return 0;
}

