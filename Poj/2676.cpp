#include <iostream>
#include <cstdio>

using namespace std;

int table[9][9];
int rows[9][10];
int cols[9][10];
int squs[9][10];

int Dfs(int r, int c)
{
	if (r == 9)
	{
		return 1;
	}
	if (table[r][c] != 0)
	{
		if (c == 8)
		{
			return Dfs(r + 1, 0);
		}
		else
		{
			return Dfs(r, c + 1);
		}
	}
	else
	{
		for (int i = 1; i < 10; i++)
		{
			if (rows[r][i] == 0 && cols[c][i] == 0 && squs[r/3*3 + c/3][i] == 0)
			{
				table[r][c] = i;
				rows[r][i] = 1;
				cols[c][i] = 1;
				squs[r/3*3 + c/3][i] = 1;
				if (c == 8)
				{
					if (Dfs(r + 1, 0) == 1)
					{
						return 1;
					}
					else
					{
						rows[r][i] = 0;
						cols[c][i] = 0;
						squs[r/3*3 + c/3][i] = 0;
						table[r][c] = 0;
					}
				}
				else
				{
					if (Dfs(r, c + 1) == 1)
					{
						return 1;
					}
					else
					{
						rows[r][i] = 0;
						cols[c][i] = 0;
						squs[r/3*3 + c/3][i] = 0;
						table[r][c] = 0;
					}
				}
			}
		}
		return 0;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("p2676","r",stdin);
#endif
	int N;
	char c;
	int i, j;
	cin >> N;
	while (N-- > 0)
	{
		for (i = 0; i < 9; i++)
		for (j = 1; j < 10; j++)
		{
			rows[i][j] = 0;
			cols[i][j] = 0;
			squs[i][j] = 0;
		}
		for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
		{
			cin >> c;
			table[i][j] = int (c - '0');
			if (c != '0')
			{
				rows[i][table[i][j]] = 1;
				cols[j][table[i][j]] = 1;
				squs[i/3*3 + j/3][table[i][j]] = 1;
			}
		}
		Dfs(0, 0);
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				cout << table[i][j];
			}
			cout << endl;
		}
	}
}