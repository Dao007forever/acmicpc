#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 4005;
char st[maxn];
int f[maxn], pre[maxn], vis[maxn];
vector<int> pos[maxn];
int n;

void output(int m) {
	if (m == 0) return;
	vis[m] = 1;
	output(pre[m]);
}

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%s", st + 1);
	n = strlen(st + 1);
	for (int i = 1; i <= n; i++) {
		int l = i, r = i;
		while (l && r <= n && st[l] == st[r]) {
			if (r != i) pos[r].push_back(l);
			l--; r++;
		}
		if (st[i] == st[i + 1]) {
			l = i; r = i + 1;
			while (l && r <= n && st[l] == st[r]) {
				pos[r].push_back(l);
				l--; r++;
			}
		}
	}
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + 1;
		pre[i] = i - 1;
		for (int j = 0; j < pos[i].size(); j++) {
			int tmp = f[pos[i][j] - 1] + 1;
			if (tmp < f[i]) {
				f[i] = tmp;
				pre[i] = pos[i][j] - 1;
			}
		}
	}
	cout << f[n] << endl;
	output(pre[n]);
	for (int i = 1; i <= n; i++) {
		printf("%c", st[i]);
		if (vis[i]) printf(" ");
	}
	return 0;
}
