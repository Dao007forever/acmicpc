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

const int maxn = 33333;
struct node {
	int l, a;
}p[maxn];
int N, L, R;
long long tot;
int tmp[maxn];

bool cmp(node A, node B) {
	if (A.l == B.l) return A.a < B.a;
	return A.l < B.l;
}

void merge(int l, int mid, int r)
{
    int i, j, t;
    t = l;
    i = l;
    j = mid + 1;
    while (t <= r)
    {
        if ((i <= mid) && ((j > r) || (p[i].a > p[j].a)))
        {
            tmp[t] = p[i].a;
            i++;
        }
        else
        {
            tmp[t] = p[j].a;
            j++;
            tot += i-l;
        }
        t++;
    }
    for (i = l; i <= r; i++)
        p[i].a = tmp[i];
}
void mergesort(int l, int r)
{
    int mid;
    mid = (l + r) / 2;
    if (l != r)
    {
        mergesort(l, mid);
        mergesort(mid + 1, r);
        merge(l, mid, r);
    }
}

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d%d", &L, &R) != EOF) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			int k, b;
			scanf("%d%d", &k, &b);
			p[i].l = k * L + b;
			p[i].a = k * R + b;
		}
		sort(p + 1, p + N + 1, cmp);
		tot = 0;
		mergesort(1, N);
		cout << tot + N + 1 << endl;
	}
	return 0;
}
