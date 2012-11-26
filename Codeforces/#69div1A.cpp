#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
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

const int INF = 1000000000;
map<string, int> name;
int like[7][7];
int score[3];
int team[7];
int min_dif, max_val;

void Init()
{
	name["Anka"] = 0;
	name["Chapay"] = 1;
	name["Cleo"] = 2;
	name["Troll"] = 3;
	name["Dracul"] = 4;
	name["Snowy"] = 5;
	name["Hexadecimal"] = 6;
	memset(like, 0, sizeof(like));
	min_dif = INF;
	max_val = 0;
}

void DFS(int s)
{
	if (s == 7)
	{
		int num[3] = {0};
		for (int i = 0; i < 7; i++)
			num[team[i]]++;
		for (int i = 0; i < 3; i++)
		if (num[i] == 0) return;
		int m_dif = 0;
		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			int a = int(score[i] / num[i]), b = int(score[j] / num[j]);
			if (abs(a - b) > m_dif)
				m_dif = abs(a - b);
		}
		int m_val = 0;
		for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
		{
			if (like[i][j] && team[i] == team[j])
				m_val++;
		}
		if (m_dif < min_dif)
		{
			min_dif = m_dif;
			max_val = m_val;
		}
		else if (m_dif == min_dif && m_val > max_val)
		{
			max_val = m_val;
		}
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		team[s] = i;
		DFS(s + 1);
		team[s] = -1;
	}
}

int main()
{
	freopen("a.txt", "r", stdin);
	Init();
	int N;
	cin >> N;
	while (N--)
	{
		string a, l, b;
		cin >> a >> l >> b;
		int x = name[a], y = name[b];
		like[x][y] = 1;
	}
	for (int i = 0; i < 7; i++)
		team[i] = -1;
	scanf("%d%d%d", &score[0], &score[1], &score[2]);
	DFS(0);
	printf("%d %d\n", min_dif, max_val);
	return 0;
}
