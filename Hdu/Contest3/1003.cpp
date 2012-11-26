#include <cstdio>

int n, m;

#define DIR_Z 1
#define DIR_X 2
#define DIR_Y 4
#define DIR_ID(ch) ((ch) == 'Z' ? 1 : ((ch) == 'X' ? 2 : 4))

struct Edge
{
	int dir;
	int x, y, z;
};

Edge edge[1024];

int readEdge(int i)
{
	char c1, c2;
	int d1, d2;
	char buff[10];
	gets(buff);
	scanf("%c=%d,%c=%d", &c1, &d1, &c2, &d2);
	if (d1 > n || d2 > n) return 0;
	c1 = DIR_ID(c1);
	c2 = DIR_ID(c2);

	if ((c1 | c2) == (DIR_X | DIR_Y))
	{
		edge[i].dir = DIR_Z;
		if (c1 == DIR_X) {edge[i].x = d1; edge[i].y = d2;}
		else {edge[i].x = d2; edge[i].y = d1;}
	}
	if ((c1 | c2) == (DIR_Y | DIR_Z))
	{
		edge[i].dir = DIR_X;
		if (c1 == DIR_Y) {edge[i].y = d1; edge[i].z = d2;}
		else {edge[i].y = d2; edge[i].z = d1;}
	}
	if ((c1 | c2) == (DIR_X | DIR_Z))
	{
		edge[i].dir = DIR_Y;
		if (c1 == DIR_X) {edge[i].x = d1; edge[i].z = d2;}
		else {edge[i].x = d2; edge[i].z = d1;}
	}

	bool used[1024] = {0};
	int p;
	if (edge[i].dir == DIR_Z)
	{
		for (p = 0; p < i; ++p)
		{
			if (edge[p].dir == DIR_Z && edge[p].x == edge[i].x
					&& edge[p].y == edge[i].y) return 0;
			if (edge[p].dir == DIR_X && edge[p].y == edge[i].y)
			{
				used[edge[p].z] = true;
			}
			if (edge[p].dir == DIR_Y && edge[p].x == edge[i].x)
			{
				used[edge[p].z] = true;
			}
		}
	}
	if (edge[i].dir == DIR_Y)
	{
		for (p = 0; p < i; ++p)
		{
			if (edge[p].dir == DIR_Y && edge[p].x == edge[i].x
					&& edge[p].z == edge[i].z) return 0;
			if (edge[p].dir == DIR_X && edge[p].z == edge[i].z)
			{
				used[edge[p].y] = true;
			}
			if (edge[p].dir == DIR_Z && edge[p].x == edge[i].x)
			{
				used[edge[p].y] = true;
			}
		}
	}
	if (edge[i].dir == DIR_X)
	{
		for (p = 0; p < i; ++p)
		{
			if (edge[p].dir == DIR_X && edge[p].z == edge[i].z
					&& edge[p].y == edge[i].y) return 0;
			if (edge[p].dir == DIR_Z && edge[p].y == edge[i].y)
			{
				used[edge[p].x] = true;
			}
			if (edge[p].dir == DIR_Y && edge[p].z == edge[i].z)
			{
				used[edge[p].x] = true;
			}
		}
	}
	int elimation = n;
	for (int t = 1; t <= n; ++t) if (used[t]) --elimation;
	return elimation;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &m);
		int ans = 0;
		int i;
		for (int i = 0; i < m; ++i) ans+=readEdge(i);
		printf("%d\n", ans);
	}
}
