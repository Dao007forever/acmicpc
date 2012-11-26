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

const int maxn = 15555;
struct Tnode {
	int id, p, c, flag;
}T[maxn];
int cnt[maxn], s[maxn];

int main()
{
	freopen("C.in", "r", stdin);
	int L, a, b, c, M;
	while (scanf("%d", &L) != EOF) {
		memset(cnt, 0, sizeof(cnt));
		M = 0;
		while (cin >> a >> b >> c) {
			if (a == -1) break;
			cnt[a] += c;
			cnt[b + 1] -= c;
		}
		s[0] = cnt[0];
		int cur = 0, Max = 0, Left, Right;
		for (int i = 1; i <= L; i++) {
			cur += cnt[i];
			s[i] = s[i - 1] + cnt[i];
			if (cur > Max) {
				Max = cur;
				Left = i;
			}
		}
		Max = 0;
		for (int i = L; i >= 1; i--) {
			if (s[i] > Max) {
				Max = s[i];
				Right = i;
			}
		}
		cout << Left << " " << Right << endl;
	}
	return 0;
}
