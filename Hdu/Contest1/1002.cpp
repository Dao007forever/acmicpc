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

const int maxn = 11111;
int A[maxn], B[maxn];

int main()
{
	freopen("1002", "r", stdin);
	int N, T;
	while (scanf("%d%d", &N, &T) != EOF)
	{
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &B[i]);
		sort(A, A + N);
		sort(B, B + N);
		int res = 0;
		for (int i = 0; i < N; i++)
		{
			if (A[i] + B[N - i - 1] > T) res += A[i] + B[N - i - 1] - T;
		}
		cout << res << endl;
	}
	return 0;
}
