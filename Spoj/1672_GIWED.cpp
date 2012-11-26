#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
struct Node
{
	int x, y;
	Node() {}
	Node(int x, int y) : x(x), y(y) {}
};
int N, M, K, L;
int x1[222], x2[222], y1[222], y2[222];
int tmpx[222], tmpy[222];
int flag[222][222], area[222];

void init()
{
	scanf("%d%d%d%d", &N, &M, &K, &L);
	for (int i = 0; i < K; i++)
		scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
	int cnt = 0;
	for (int i = 0; i < K; i++)
		tmpx[i] = x1[i], tmpx[i + K] = x2[i];
	tmpx[2 * K] = N; tmpx[2 * K + 1] = 0;
	sort(tmpx, tmpx + 2 * K + 2);
	for (int i = 1; i <= 2 * K + 1; i++)
		if (tmpx[i] != tmpx[i - 1])
			tmpx[++cnt] = tmpx[i];
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j <= cnt; j++)
		if (x1[i] == tmpx[j])
		{
			x1[i] = j;
			break;
		}
		for (int j = 0; j <= cnt; j++)
		if (x2[i] == tmpx[j])
		{
			x2[i] = j;
			break;
		}
	}
	for (int i = 0; i <= cnt; i++)
		if (tmpx[i] == N) N = i;

	cnt = 0;
	for (int i = 0; i < K; i++)
		tmpy[i] = y1[i], tmpy[i + K] = y2[i];
	tmpy[2 * K] = M; tmpy[2 * K + 1] = 0;
	sort(tmpy, tmpy + 2 * K + 2);
	for (int i = 1; i <= 2 * K + 1; i++)
		if (tmpy[i] != tmpy[i - 1])
			tmpy[++cnt] = tmpy[i];
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j <= cnt; j++)
		if (y1[i] == tmpy[j])
		{
			y1[i] = j;
			break;
		}
		for (int j = 0; j <= cnt; j++)
		if (y2[i] == tmpy[j])
		{
			y2[i] = j;
			break;
		}
	}
	for (int i = 0; i <= cnt; i++)
		if (tmpy[i] == M) M = i;
}

void solve()
{
	for (int i = 0; i < N; i++)
	for (int j = 0; j < M; j++)
		flag[i][j] = true;
	for (int i = 0; i < K; i++)
	for (int u = x1[i]; u < x2[i]; u++)
	for (int v = y1[i]; v < y2[i]; v++)
		flag[u][v] = false;
//printf("%d\n", flag[1][3]);
	int cnt = 0;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < M; j++)
	if (flag[i][j])
	{
		queue<Node> Q;
		Node node(i, j);
		Q.push(node);
		int sum = 0;
		flag[i][j] = false;
		while (!Q.empty())
		{
			Node now = Q.front();
			Q.pop();
			sum += (tmpx[now.x + 1] - tmpx[now.x]) * (tmpy[now.y + 1] - tmpy[now.y]);
//printf("%d\n", (tmpx[now.x + 1] - tmpx[now.x]) * (tmpy[now.y + 1] - tmpy[now.y]));
//printf("%d %d %d %d\n", tmpx[now.x], tmpy[now.y], tmpx[now.x + 1], tmpy[now.y + 1]);
			for (int k = 0; k < 4; k++)
			{
				int x = now.x + dx[k], y = now.y + dy[k];
				/*if (x == 1 && y == 3)
				{
					printf("!!!!!!!!!!!\n");
					printf("%d\n", flag[1][3]);
				}*/
				if (x >= 0 && x < N && y >= 0 && y < M && flag[x][y])
				{
//printf("%d %d\n", x, y);
					flag[x][y] = false;
					node.x = x; node.y = y;
					Q.push(node);
				}
			}
		}
		area[cnt++] = sum;
	}
	sort(area, area + cnt);
	int ans = 0;
	for (int i = cnt - 1; i >= 0 && cnt - i <= L; i--)
		ans += area[i];
	printf("%d\n", ans);
}

int main()
{
	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		solve();
	}
	return 0;
}
