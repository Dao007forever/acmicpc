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

const int N = 9;
const int MAXM = 4 * N * N;
const int MAXN = N * N * N;
const int MAX = MAXN * MAXM + 10;
const int inf =0x7ffffff;
int L[MAX], R[MAX], U[MAX], D[MAX], C[MAX], row[MAX], H[MAXN + 10];//C[x]是指向其列指针头的地址，S[i]记录列链表中结点的总数，O[x]用来记录结果
int S[MAX], O[MAX];
int size, n, m, res;
char ans[10][10];

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

void Link(int r, int c)
{
	row[size] = r;
	S[c]++;
	C[size] = c;
	U[size] = c; D[size] = D[c];
	U[D[c]] = size; D[c] = size;
	if (H[r] == -1)
	{
		H[r] = L[size] = R[size] = size;
	}
	else
	{
		L[size] = H[r]; R[size] = R[H[r]];
		L[R[H[r]]] = size; R[H[r]] = size;
	}
	size++;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	int cas = Test;
	while (Test--)
	{
		for (int i = 0; i < MAXM; i++)
		{
			S[i] = 0;
			D[i] = U[i] = i;
			L[i + 1] = i;
			R[i] = i + 1;
		}
		R[MAXM] = 0;
		L[0] = MAXM;
		size = MAXM + 1;
		memset(H, -1, sizeof(H));
		char str[12][12];
		char ss[12];
		if (Test < cas - 1) scanf("%s", ss);
		for (int i = 0; i < 9; i++)
			scanf("%s", str[i]);

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int b = i / 3 * 3 + j / 3;
				if (str[i][j] == '?')
				{
					for (int k = 1; k <= n; k++)
					{
						int r = i * 9 * 9 + j * 9 + k;
						Link(r, i * 9 + j + 1);
						Link(r, 81 + i * 9 + k);
						Link(r, 162 + j * 9 + k);
						Link(r, 243 + b * 9 + k);
					}
				}
				else
				{
					int k = str[i][j] - '0';
					int r = i * 9 * 9 + j * 9 + k;
					Link(r, i * 9 + j + 1);
					Link(r, 81 + i * 9 + k);
					Link(r, 162 + j * 9 + k);
					Link(r, 243 + b * 9 + k);
				}
			}
		}
		if (dfs(0))
		{
			for (int p = 0; p < res; p++)
			{
				int t = row[O[p]] - 1;
				int k = t % 9; t /= 9;
				int j = t % 9; t /= 9;
				int i = t % n;
				ans[i][j] = '1' + k;
			}
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					printf("%d", ans[i][j]);
				}
				printf("\n");
			}
		}
		else
		{
			puts("impossible\n");
		}
		if (Test) puts("---");
	}
	return 0;
}
