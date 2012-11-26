#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n;
struct person {
	int s, b, id;
}p[maxn];
int size, ansp;
int C[maxn], f[maxn], pos[maxn], pre[maxn];

bool cmp(person A, person B) {
	if (A.s != B.s) return A.s < B.s;
	return A.b < B.b;
}

int bsearch(int x) {
	int l = 0, r = size + 1;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (C[mid] < x) l = mid;
		else r = mid;
	}
	return l;
}

void solve() {
	size = 0;
	memset(f, 0xff, sizeof(f));
	fill(C + 1, C + n + 1, 0x7fffffff);
	C[0] = -1;
	pos[0] = -1;
	for (int i = 0; i < n; i++) {
		if (i && p[i].s != p[i - 1].s)
			for (int j = i - 1; j >= 0 && p[j].s == p[i - 1].s; j--)
				if (p[j].b < C[f[j]])
				C[f[j]] = p[j].b, pos[f[j]] = j;
		int tmp = bsearch(p[i].b);
		f[i] = tmp + 1;
		pre[i] = pos[tmp];
		if (f[i] > size) size = f[i], ansp = i;
	}
}

/*void solve() {
	size = 1;
	memset(C, -1, sizeof(C));
	memset(pre, -1, sizeof(pre));
	C[0] = p[0].b;
	for (int i = 1; i < n; i++) {
		if (p[i].b > C[size - 1]) {
			size++;
			C[size - 1] = p[i].b;
			pos[size - 1] = i;
		}else {
			int tmp = bsearch(p[i].b);
			C[tmp] = p[i].b;
			pre[i] = pos[tmp];
			ansp = i;
		}
	}
}*/

void Print(int k) {
	if (pre[k] != -1) {
		Print(pre[k]);
		printf(" ");
	}
	printf("%d", p[k].id);
}

void output() {
	printf("%d\n", size);
	Print(ansp);
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	cin >> Test;
	int blank = false;
	while (Test--) {
		if (blank) puts("");
		blank = true;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> p[i].s >> p[i].b;
			p[i].id = i + 1;
		}
		sort(p, p + n, cmp);
		solve();
		output();
	}
	return 0;
}
