#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 100000 + 10;
int N;
int a[MAXN], b[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", b + i);
	int t1 = 0, t2 = 1;
	for (int i = 1; i <= N; i++)
	{
		a[++t1] = i;
		for (; t1 && a[t1] == b[t2]; t1--, t2++);
	}
	if (t1) cout << "Cheater" << endl;
	else cout << "Not a proof" << endl;
	return 0;
}
