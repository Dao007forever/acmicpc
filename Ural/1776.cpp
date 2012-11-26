/*
 * P(i,j)表示发射连续的前i个火箭用了j次的概率，Psum(i,j)=P(i,0)+P(i,1)+...+P(i,j-1)
 */
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

const int maxn = 405;
int n;
double P[maxn][maxn], Psum[maxn][maxn];

int main()
{
	cin >> n;
	n -= 2;
	memset(P, 0, sizeof(P));
	memset(Psum, 0, sizeof(Psum));
	P[0][0] = 1.0;
	for (int i = 1; i <= n; i++)
		Psum[0][i] = 1.0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 0; k <= i - 1; k++)
				P[i][j] += P[k][j - 1] * P[i - k - 1][j - 1] + P[k][j - 1] * Psum[i - k - 1][j - 1] + P[i - k - 1][j - 1] * Psum[k][j - 1];
			P[i][j] /= i;
		}
		for (int j = 1; j <= n; j++)
			Psum[i][j] = Psum[i][j - 1] + P[i][j - 1];
	}
	double ret = 0;
	for (int i = 1; i <= n; i++)
		ret += P[n][i] * i;
	printf("%.6lf\n", ret * 10);
	return 0;
}
