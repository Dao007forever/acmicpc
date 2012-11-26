#include <map>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 105;
int n;
int a[111];
struct node {
	int n, val;
};
node vec[maxn * maxn * maxn];

bool cmp(node A, node B) {
	return A.val < B.val;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
    for (int i = 0; i < n; i++)
		scanf("%d", a + i);

	int m = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				int t = a[i] * a[j] + a[k];
				vec[m++].val = t;
			}
	sort(vec, vec + m, cmp);
	vec[0].n = 1;
	int M = m;
	m = 0;
	for (int i = 1; i < M; i++)
		if (vec[i].val == vec[m].val) vec[m].n++;
		else {
			vec[++m].val = vec[i].val;
			vec[m].n = 1;
		}
	
	long long ret = 0;
    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				if (a[k] == 0) continue;
				int t = (a[i] + a[j]) * a[k];
				int l = 0, r = m;
				while (l <= r) {
					int mid = (l + r) >> 1;
					if (t == vec[mid].val) {
						ret += vec[mid].n;
						break;
					}
					if (t < vec[mid].val) r = mid - 1;
					else l = mid + 1;
				}
			}
	cout << ret << endl;
	return 0;
}
