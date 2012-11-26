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

int N, R, ret;
int a[100005], Next[100005], que[100005], h[100005];

void output() {
	cout << ret << endl;
	memset(h, false, sizeof(h));
	for (int i = 1; i <= N; i++)
		if (!h[i]) {
			int k = 0;
			for (int j = i; j; j = Next[j]) {
				k++;
			}
			printf("%d", k);
			for (int j = i; j; j = Next[j]) {
				printf(" %d", j);
				h[j] = true;
			}
			printf("\n");
		}
}

int main() {
	freopen("in", "r", stdin);
	cin >> N >> R;
	for (int i = 1; i <= N; i++)
		cin >> a[i];
	int head = 1, tail = 0;
	ret = 0;
	for (int i = 1; i <= N; i++) {
		if (head > tail || a[i] - a[que[head]] <= R) ret++;
		else {
			Next[que[head]] = i;
			head++;
		}
		tail++;
		que[tail] = i;
	}
	output();
	return 0;
}
