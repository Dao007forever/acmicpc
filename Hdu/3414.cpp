/*
 * Author: Yang Zhang
 * Created Time: Thu 16 Aug 2012 10:11:59 PM UTC
 * File Name: 3414_1.cpp
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

//Hamilton circuit, take every vertex as a start and check g[arr[n-1]][arr[0]]
#define maxn 1005
bool g[maxn][maxn];
int n, cnt;
int arr[maxn];
bool hamilton(int start) {
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
	if (g[arr[n - 1]][arr[0]]) {
		for (int i = 0; i < n; i++) {
			if (i != 0) printf(" ");
			printf("%d", arr[i] + 1);
		}
		puts("");
		return true;
	}
	return false;
}
//hdu 3414
int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				int x;
				scanf("%d", &x);
				g[i][j] = x;
			}
		if (n == 1) {
			printf("1\n");
			continue;
		}
		bool flag = false;
		for (int i = 0; i < n && !flag; i++) {
			if (hamilton(i)) {
				flag = true;
			}
		}
		if (!flag) puts("-1");
	}
	return 0;
}

