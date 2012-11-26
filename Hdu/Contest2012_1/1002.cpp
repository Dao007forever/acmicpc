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

int cnt[10];
int f[33];

int main() {
	freopen("A.in", "r", stdin);
	char s[1111];
	while (scanf("%s", s) != EOF) {
		for (int i = 1; i <= 6; i++)
			cnt[i] = 4;
		int len = strlen(s), sum = 0;
		for (int i = 0; i < len; i++) {
			cnt[s[i] - '0']--;
			sum += s[i] - '0';
		}
		if (sum >= 31) {
			if (len & 1) printf("%s A\n", s);
			else printf("%s B\n", s);
			continue;
		}
		sum = 31 - sum;
		memset(f, -1, sizeof(f));
		f[0] = 0;
		for (int i = 1; i <= 6; i++)
			for (int j = 1; j <= cnt[i]; j++)
				for (int k = sum; k >= 0; k--)
					if (k - j * i >= 0 && f[k - j * i] != -1)
						f[k] = 1 - f[k - j * i];
		if (len & 1) {
			if (f[sum]) printf("%s B\n", s);
			else printf("%s A\n", s);
		} else {
			if (f[sum]) printf("%s A\n", s);
			else printf("%s B\n", s);
		}
	}
}
