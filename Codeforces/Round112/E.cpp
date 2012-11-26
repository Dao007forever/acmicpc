#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[1000001];
int f[5000001];
int n;

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		f[a[i] ^ ((1 << 22) - 1)] = a[i];
	}
	for (int i = ((1 << 22) - 1); i >= 0; i--)
		if (!f[i]) {
			for (int j = 0; j < 22; j++)
				if (f[i | (1 << j)]) {
					f[i] |= f[i | (1 << j)];
					break;
				}
		}
	for (int i = 0; i < n; i++)
		if (f[a[i]])
			printf("%d ", f[a[i]]);
		else printf("-1 ");
	return 0;
}
