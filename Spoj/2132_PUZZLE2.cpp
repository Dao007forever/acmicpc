#include <cstdio>
#include <cstdlib>

const int MAX = 100;
int n, m;
char str[11];
char **A, **B, **h;
char s[111][111];

void init()
{
	A = new char*[MAX];
	B = new char*[MAX];
	h = new char*[MAX];
	for (int i = 0; i < MAX; i++)
	{
		A[i] = new char[MAX];
		B[i] = new char[MAX];
		h[i] = new char[MAX];
	}
}

void deinit()
{
	for (int i = 0; i < MAX; i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] h[i];
	}
	delete[] A;
	delete[] B;
	delete[] h;
}

void flip(int r, char** w)
{
	for (int i = 0; i < m; i++)
		w[r][i] = 1 - w[r][i];
}

void blueCol(int c, char** w)
{
	for (int i = 0; i < n; i++)
		if (w[i][c] == 1) flip(i, w);
}

bool compare()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (A[i][j] != B[i][j]) return 0;
	return 1;
}

int cmp(const void *a, const void *b)
{
	char *col1, *col2;
	col1 = (char *)a;
	col2 = (char *)b;
	int n1 = 0, n2 = 0, ret;
	for (int i = 0; i < n; i++)
	{
		n1 += col1[i];
		n2 += col2[i];
		if (col1[i] < col2[i]) ret = 1;
		if (col1[i] > col2[i]) ret = -1;
	}
	if (n1 < n2) return 1;
	if (n1 > n2) return -1;
	return ret;
}

void sort(char** w)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			s[j][i] = w[i][j];
	qsort((void *)s, m, sizeof(s[0]), cmp);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			w[i][j] = s[j][i];
}

bool possible()
{
	for (int i= 0; i < n; i++)
		for (int j = 0; j < m; j++)
			h[i][j] = B[i][j];
	blueCol(0, A);
	sort(A);
	for (int k = 0; k < m; k++)
	{
		blueCol(k, B);
		sort(B);
		if (compare()) return 1;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				B[i][j] = h[i][j];
	}
	return 0;
}

int main()
{
	freopen("f.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				scanf("%s", str);
				A[i][j] = (*str == 'R');
			}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				scanf("%s", str);
				B[i][j] = (*str == 'R');
			}
		if (possible()) printf("YES\n");
		else printf("NO\n");
		deinit();
	}
	return 0;
}
