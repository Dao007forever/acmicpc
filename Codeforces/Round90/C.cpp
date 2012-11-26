#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long n, m, k;
struct Node
{
	long long a, b, c;
	int id;
}p[111];
long long dp[111][111][111];
int pre[111][111][111][2];

bool cmp(const Node &A, const Node &B)
{
	return A.c < B.c;
}

void output(int i, int s, int j)
{
	int pos;
	if (s == 1)
	{
		cout << p[i].id << " " << p[i].a + j << endl;
		return;
	}
	else
	{
		pos = pre[i][s][j][0];
		if (pre[i][s][j][1] == 0)
			output(pos, s - 1, (p[i].a + j) / k - p[pos].a);
		else output(pos, s - 1, (p[i].a + j) - k - p[pos].a);
		cout << p[i].id << " " << p[i].a + j << endl;
	}
}

int main()
{
	freopen("in", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
	{
		cin >> p[i].a >> p[i].b >> p[i].c;
		p[i].id = i;
	}
	sort(p + 1, p + m + 1, cmp);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= m; i++)
		for (int j = 0; j <= 100 && p[i].a + j <= p[i].b; j++)
			dp[i][1][j] = p[i].a + j;
	for (int s = 1; s < n; s++)
	{
		for (int i = 1; i <= m; i++)
		{
			for (int j = 0; j <= 100 && p[i].a + j <= p[i].b; j++)
			{
				if (dp[i][s][j] == -1) continue;
				for (int q = i + 1; q <= m; q++)
				if (p[q].c > p[i].c)
				{
					long long tmp = (p[i].a + j) * k;
					if (tmp >= p[q].a && tmp <= p[q].b)
					{
						if (dp[q][s + 1][tmp - p[q].a] < dp[i][s][j] + tmp)
						{
							dp[q][s + 1][tmp - p[q].a] = dp[i][s][j] + tmp;
							pre[q][s + 1][tmp - p[q].a][0] = i;
							pre[q][s + 1][tmp - p[q].a][1] = 0;
						}
					}
					
					tmp = (p[i].a + j) + k;
					if (tmp >= p[q].a && tmp <= p[q].b)
					{
						if (dp[q][s + 1][tmp - p[q].a] < dp[i][s][j] + tmp)
						{
							dp[q][s + 1][tmp - p[q].a] = dp[i][s][j] + tmp;
							pre[q][s + 1][tmp - p[q].a][0] = i;
							pre[q][s + 1][tmp - p[q].a][1] = 1;
						}
					}
				}
			}
		}
	}
	long long tmp = -1;
	int ii, jj;
	for (int i = n; i <= m; i++)
		for (int j = 0; j <= 100; j++)
		if (dp[i][n][j] >= tmp)
		{
			tmp = dp[i][n][j];
			ii = i;
			jj = j;
		}
	if (tmp == -1) printf("NO\n");
	else
	{
		printf("YES\n");
		output(ii, n, jj);
	}
	return 0;
}
