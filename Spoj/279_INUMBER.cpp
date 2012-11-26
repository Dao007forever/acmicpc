/*
 * Author : Yang Zhang
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
/*------------#include omitted-----------*/
#define MAXN 1005
#define MAXQ 1000005
int n;
int qs[MAXQ], qm[MAXQ], pre[MAXQ], md[MAXN];
int vst[MAXN][MAXN];

void output(int now) {
	if (now == 0) return;
	output(pre[now]);
	printf("%d", qs[now] - qs[pre[now]]);
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			md[i] = i * 10 % n;
		int head = 0, tail = 0;
		qs[tail] = 0, qm[tail] = 0;
		tail++;
		while (head < tail) {
			int s = qs[head], m = qm[head];
			if (s == n && m == 0) {
				output(head);
				break;
			}
			for (int i = 0; i < 10; i++) {
				int news = s + i, newm = (md[m] + i) % n;
				if (news > n) continue;
				if (vst[news][newm] != cas) {
					vst[news][newm] = cas;
					qs[tail] = news; qm[tail] = newm;
					pre[tail] = head;
					tail++;
				}
			}
			head++;
		}
		puts("");
	}
	return 0;
}
