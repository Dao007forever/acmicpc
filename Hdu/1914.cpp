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

const int MAXN = 100 + 10;
int N;
int mlove[MAXN][MAXN], wlove[MAXN][MAXN], couple[MAXN], pare[MAXN];
queue<int> SQ;

void dfs()
{
	int woman, man;
	while (!SQ.empty())
		SQ.pop();
	memset(couple, -1, sizeof(couple));

	for (int i = 1; i <= N; i++)
		SQ.push(i);

	while (!SQ.empty())
	{
		man = SQ.front();
		SQ.pop();
		for (int i = 1; i <= N; i++)
		{
			if (mlove[man][i] != -1)
			{
				woman = mlove[man][i];
				mlove[man][i] = -1;
				int pre = couple[woman];
				if (pre == -1)
				{
					couple[woman] = man;
					pare[man] = woman;
					break;
				}
				else
				{
					if (wlove[woman][man] > wlove[woman][pre])
					{
						SQ.push(pre);
						couple[woman] = man;
						pare[man] = woman;
						break;
					}
				}
			}
		}
	}
}

int Hash[256];
char m_rev[256], w_rev[256], str[1000];
int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++)
	{
		memset(Hash, 0, sizeof(Hash));
		scanf("%d\n", &N);
		for (int i = 1; i <= N; i++)
		{
			char ch;
			scanf("%c ", &ch);
			Hash[ch] = i;
			m_rev[i] = ch;
		}
		for (int i = 1; i <= N; i++)
		{
			char ch;
			scanf("%c ", &ch);
			Hash[ch] = i;
			w_rev[i] = ch;
		}

		for (int i = 1; i <= N; i++)
		{
			char ch;
			scanf("%c:%s", &ch, str);
			getchar();
			for (int j = 1; j <= N; j++)
			{
				mlove[Hash[ch]][j] = Hash[str[j - 1]];
			}
		}
		for (int i = 1; i <= N; i++)
		{
			char ch;
			scanf("%c:%s", &ch, str);
			getchar();
			for (int j = 1; j <= N; j++)
			{
				wlove[Hash[ch]][Hash[str[j - 1]]] = N - j;
			}
		}

		dfs();

		for (int i = 'a'; i <= 'z'; i++)
		{
			if (Hash[i])
			{
				printf("%c %c\n", i, w_rev[pare[Hash[i]]]);
			}
		}
		if (cas < T) printf("\n");
	}
	return 0;
}
