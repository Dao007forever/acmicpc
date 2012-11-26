#include <cstdio>
#include <cstring>

int N, M;
int p[222222];

int find(int x)
{
	if (p[x] == -1) return x;
	return p[x] = find(p[x]);
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d", &N, &M);
	memset(p, -1, sizeof(p));
	for (int i = 1; i <= M; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (find(x) != find(y + N))
			p[find(x)] = find(y + N);
		if (find(x + N) != find(y))
			p[find(x + N)] = find(y);
	}
	int ans = 1;
	for (int i = 0; i < N; i++)
		if (find(i) == find(i + N)) ans = 2;
	printf("%d\n", ans);
	return 0;
}
