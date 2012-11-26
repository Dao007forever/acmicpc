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

const int MAXM = 350;
const int MAXN = 750;
const int MAX = MAXN * MAXM;
const int inf =0x7ffffff;
int L[MAX], R[MAX], U[MAX], D[MAX], C[MAX];//C[x]是指向其列指针头的地址，S[i]记录列链表中结点的总数，O[x]用来记录结果
int S[MAXN], O[MAXM];
int size, n, m, res;
int Map[MAXN][MAXM];
int ans[10][10];

void remove(int c)//删除一列并删除同列覆盖的每行
{
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i])
    {
        for (int j = R[i]; j != i; j = R[j])
        {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            S[C[j]]--;
        }
    }
}

void resume(int c)//恢复一列及此列覆盖的行
{
    for (int i = U[c]; i != c; i = U[i])
    {
        for (int j = L[i]; j != i; j = L[j])
        {
            U[D[j]] = j;
            D[U[j]] = j;
            S[C[j]]++;
        }
    }
    L[R[c]] = c;
    R[L[c]] = c;
}

bool dfs(int k)
{
    if (!R[0])//得到结果，相当于论文中的R[head]==head(因为head=0)
    {
		res = k;
        return true;
    }
    int Min = inf, c;
    for (int i = R[0]; i; i = R[i])
        if (S[i] < Min) Min = S[i], c = i;
    remove(c);
    for (int i = D[c]; i != c; i = D[i])
    {
        for (int j = R[i]; j != i; j = R[j])
            remove(C[j]);//删除
        O[k] = (i - 1) / m;//记录结果
        if (dfs(k + 1)) return true;
        for (int j = L[i]; j != i; j = L[j])
            resume(C[j]);//恢复
    }
    resume(c);
    return false;
}

void build()
{
	memset(S, 0, sizeof(S));
	for (int i = 1; i <= m; i++)
		R[i - 1] = L[i + 1] = U[i] = D[i] = i;
	R[0] = 1; R[m] = 0;
	size = m + 1;
	for (int i = 1; i <= n; i++)
	{
		int rowh = -1;
		for (int j = 1; j <= m; j++)
		{
			if (Map[i][j] == 1)
			{
				C[size] = j;

				U[size] = U[j];
				D[U[j]] = size;
				U[j] = size;
				D[size] = j;

				S[j]++;

				if (rowh == -1)
				{
					L[size] = R[size] = size;
					rowh = size;
				}
				else
				{
					L[size] = L[rowh];
					R[L[rowh]] = size;
					L[rowh] = size;
					R[size] = rowh;
				}
				size++;
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	int cas = Test;
	while (Test--)
	{
		char str[12][12];
		char ss[12];
		if (Test < cas - 1) scanf("%s", ss);
		for (int i = 1; i <= 9; i++)
			scanf("%s", str[i] + 1);

		memset(Map, 0, sizeof(Map));
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				int t = (i - 1) * 9 + j;
				if (str[i][j] == '?')
				{
					for (int k = 1; k <= 9; k++)
					{
						Map[9 * (t - 1) + k][t] = 1;
						Map[9 * (t - 1) + k][81 + (i - 1) * 9 + k] = 1;
						Map[9 * (t - 1) + k][162 + (i - 1) * 9 + k] = 1;
						Map[9 * (t - 1) + k][243 + ((i - 1) / 3 * 3 + (j + 2) / 3 - 1) * 9 + k] = 1;
					}
				}
				else
				{
					int k = str[i][j] - '0';
					Map[9 * (t - 1) + k][t] = 1;
					Map[9 * (t - 1) + k][81 + (i - 1) * 9 + k] = 1;
					Map[9 * (t - 1) + k][162 + (i - 1) * 9 + k] = 1;
					Map[9 * (t - 1) + k][243 + ((i - 1) / 3 * 3 + (j + 2) / 3 - 1) * 9 + k] = 1;
				}
			}
		}
		n = 729;
		m = 324;
		build();
		if (!dfs(0))
		{
			printf("impossible\n");
			continue;
		}
		int x, y, k;
		for (int i = 0; i < res; i++)
		{
			int r = O[i];
			k = r % 9;
			if (k == 0) k = 9;
			int num = (r - k) / 9 + 1;
			y = num % 9;
			if (y == 0) y = 9;
			x = (num - y) / 9 + 1;
			ans[x][y] = k;
		}
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
				printf("%d", ans[i][j]);
			printf("\n");
		}
		if (Test) printf("---\n");
	}
	return 0;
}

