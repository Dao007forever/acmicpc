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

const int MAXN = 20;
const int MAX = 65536;
const int inf = 0x3f3f3f3f;
int T, N;
struct Course
{
	string name;
	int D, C;
}course[MAXN];
string str[MAXN], outs[MAXN];
int Pow[16] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
int dp[MAX];
bool vis[MAX];

void dfs(int days, int cost, int sta, int num)
{
	if (num == N)
	{
		if (dp[sta] == cost)
		{
			for (int i = 0; i < num; i++)
				outs[i] = str[i];
		}
		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (!vis[i])
		{
			vis[i] = true;
			sta += Pow[i];
			int temp = days + course[i].C - course[i].D;
			if (temp < 0) temp = cost;
			else temp += cost;
			if (temp < dp[sta])
			{
				dp[sta] = temp;
				str[num++] = course[i].name;
				dfs(days + course[i].C, temp, sta, num);
				num--;
			}
			sta -= Pow[i];
			vis[i] = false;
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	cin >> T;
	while (T--)
	{
		cin >> N;
		int upper = 1 << N;
		for (int i = 1; i <= N; i++)
			cin >> course[i].name >> course[i].D >> course[i].C;
		for (int i = 0; i < upper; i++)
			dp[i] = inf;
		memset(vis, 0, sizeof(vis));
		dfs(0, 0, 0, 0);
		cout << dp[upper - 1] << endl;
		for (int i = 0; i < N; i++)
			cout << outs[i] << endl;
	}
	return 0;
}
