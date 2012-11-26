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

struct Min
{
    int u, d;
    bool operator <(const Min it)const
    {
		if (d == it.d) return u > it.u;
        return d > it.d;
    }
};
struct Max
{
    int u, d;
    bool operator <(const Max it)const
    {
		if (d == it.d) return u < it.u;
        return d < it.d;
    }
};

priority_queue<Min> Qmin;
priority_queue<Max> Qmax;
vector<int> a, b;
bool cmp(int i, int j) {
	return b[i] > b[j];
}
int main()
{
	freopen("in", "r", stdin);
	int n, k1, k2;
	int cas = 1;
	while (scanf("%d%d%d", &n, &k1, &k2) != EOF) {
		if (n == 0 && k1 == 0 && k2 == 0) break;
		printf("Case %d\n", cas++);
		while (!Qmin.empty())
			Qmin.pop();
		while (!Qmax.empty())
			Qmax.pop();
		a.clear();
		b.clear();
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			Min s1; Max s2;
			s1.d = x; s1.u = i;
			s2.d = x; s2.u = i;
			Qmin.push(s1);
			Qmax.push(s2);
		}
		for (int i = 0; i < k1; i++) {
			Min ret = Qmin.top();
			Qmin.pop();
			a.push_back(ret.u + 1);
//			printf("%d ", ret.u + 1);
		}
		sort(a.begin(), a.end());
		for (int i = 0; i < a.size() - 1; i++)
			printf("%d ", a[i]);
		printf("%d\n", a[a.size() - 1]);
		for (int i = 0; i < k2; i++) {
			Max ret = Qmax.top();
			Qmax.pop();
			b.push_back(ret.u + 1);
//			printf("%d ", ret.u + 1);
		}
		sort(b.begin(), b.end());
		reverse(b.begin(), b.end());
		for (int i = 0; i < b.size() - 1; i++)
			printf("%d ", b[i]);
		printf("%d\n", b[b.size() - 1]);
	}
	return 0;
}
