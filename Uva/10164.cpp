#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3000 + 10;
int N;
int a[MAXN], even[MAXN], odd[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while (cin >> N && N)
	{
		int no = 0, ne = 0;
		for (int i = 1; i <= 2 * N - 1; i++)
		{
			cin >> a[i];
			if (a[i] & 1) odd[++no] = a[i];
			else even[++ne] = a[i];
		}
		cout << "Yes" << endl;
		int i;
		if (no & 1) no--;
		for (i = 1; i <= min(N, no); i++)
			cout << odd[i] << " ";
		if (i < N)
		{
			for (int j = i; j <= N; j++)
				cout << even[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
