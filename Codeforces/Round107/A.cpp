#include <cmath>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 4000000;
long long p;
int pr[maxn + 5], len = 0;
bool f[maxn];

int main() {
	freopen("in.txt", "r", stdin);
	cin >> p;
	memset(f, 1, sizeof(f));
	for (int i = 2; i <= maxn; i++)
		if (f[i]) {
			pr[len++] = i;
			for (int j = 2; i * j <= maxn; j++)
				f[i * j] = false;
		}
	vector<long long> fac;
	fac.clear();
	for (int i = 0; i < len && (long long)pr[i] * pr[i] <= p; i++) {
		while (p % pr[i] == 0) {
			fac.push_back(pr[i]);
			p /= pr[i];
		}
	}
	if (p > 1) fac.push_back(p);
	if (fac.size() == 2) {
		cout << 2 << endl;
	} else {
		cout << 1 << endl;
		if (fac.size() > 2)
			cout << fac[0] * fac[1] << endl;
		else cout << 0 << endl;
	}
	return 0;
}
