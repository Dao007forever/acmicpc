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
#define sqr(v) ((double)(v) * (v))
const int MAXN = 101000;
const double eps = 1e-10;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}
int X[MAXN], Y[MAXN], R[MAXN];//原始圆
int n;//圆的个数
int LL[MAXN], RR[MAXN];//按照左边界和右边界排序的圆下标，这两个是事件点
int tmp[MAXN], num[MAXN];//tmp[i]表示纵坐标排序第i名的为tmp[i],num是tmp的反函数

set<int> tree;//树，保存信息
double mid;//当前搜索的点

double collid(int a, int b)//排名为a的和排名为b的是否碰撞
{
	a = tmp[a];
	b = tmp[b];
	if (sqr(X[a] - X[b]) + sqr(Y[a] - Y[b]) - sqr(R[a] + R[b] + mid + mid) <= 0)
		return true;
	return false;
}

bool insert(int v)//是否将排名为v的点插入成功
{
	set<int>::iterator it = tree.insert(v).first;
	if (it != tree.begin())
	{
		if (collid(v, *--it))
			return false;
		++it;
	}
	if (++it != tree.end())
	{
		if (collid(v, *it))
		{
			return false;
		}
	}
	return true;
}

bool remove(int v)//是否将排名为v的点删除成功
{
	set<int>::iterator it = tree.find(v);
	if (it == tree.end())
		printf("error\n");
	if (it != tree.begin() && it != --tree.end())
	{
		int a = *--it;
		++it;
		int b = *++it;
		if (collid(a, b)) return false;
	}
	tree.erase(v);
	return true;
}

bool check(double mid)//二分每一次判断是否可行
{
	::mid = mid;
	tree.clear();
	int l = 0, r = 0;
	while (l < n || r < n)
	{
		if (l == n)
		{
			if (!remove(num[RR[r++]]))
				return false;
		}
		else if (r == n)
		{
			if (!insert(num[LL[l++]]))
				return false;
		}
		else if (dblcmp(X[LL[l]] - R[LL[l]] - mid - X[RR[r]] - R[RR[r]] - mid) <= 0)
		{
			if (!insert(num[LL[l++]]))
				return false;
		}
		else
		{
			if (!remove(num[RR[r++]]))
				return false;
		}
	}
	return true;
}

bool cmpy(int a, int b)//按照y坐标关键字排序
{
	if (Y[a] == Y[b])
		return X[a] < X[b];
	return Y[a] < Y[b];
}

bool cmpl(int a, int b)//进入圆时的事件点
{
	return X[a] - R[a] < X[b] - R[b];
}

bool cmpr(int a, int b)//离开圆时的事件点
{
	return X[a] + R[a] < X[b] + R[b];
}

double solve()//求最近圆对
{
	for (int i = 0; i < n; i++)
	{
		tmp[i] = RR[i] = LL[i] = i;
	}
	sort(tmp, tmp + n, cmpy);
	for (int i = 0; i < n; i++)
	{
		num[tmp[i]] = i;
	}
	sort(LL, LL + n, cmpl);
	sort(RR, RR + n, cmpr);
	double s = 0, t = sqr(sqrt(sqr(X[0] - X[1]) + sqr(Y[0] - Y[1])) - R[0] - R[1]);
	while (t - s > 1e-8)
	{
		double mid = (s + t) / 2;
		if (check(mid)) s = mid;
		else t = mid;
	}
	return s + t;
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &X[i], &Y[i], &R[i]);
		printf("%.6lf\n", solve());
	}
	return 0;
}
