bool mat[22][22];
int n, m;

bool planarity() {
	bool change;
	do {
		change = false;
		for (int i = 1; i <= n; i++) {
			int cnt = 0;
			mat[i][i] = false;
			for (int j = 1; j <= n; j++)
				cnt += mat[i][j];
			if (cnt == 1) {
				for (int j = 1; j <= n; j++) {
					mat[i][j] = mat[j][i] = false;
				}
				change = true;
			}
			if (cnt == 2) {
				change = true;
				int a = 0, b = 0;
				for (int j = 1; j <= n; j++) {
					if (mat[i][j]) {
						if (a == 0) a = j;
						else b = j;
					}
				}
				mat[a][b] = mat[b][a] = true;
				mat[a][i] = mat[i][a] = false;
				mat[b][i] = mat[i][b] = false;
			}
		}
	} while (change);

	for (int a = 1; a <= n; a++)
		for (int b = a + 1; b <= n; b++) {
			if (mat[a][b]) {
				for (int c = b + 1; c <= n; c++) {
					if (mat[a][c] && mat[b][c]) {
						for (int d = c + 1; d <= n; d++) {
							if (mat[a][d] && mat[b][d] && mat[c][d]) {
								for (int e = d + 1; e <= n; e++) {
									if (mat[a][e] && mat[b][e] && mat[c][e] && mat[d][e])
										return false;
								}
							}
						}
					}
				}
			}
		}

	for (int a = 1; a <= n; a++)
		for (int b = a + 1; b <= n; b++)
			for (int c = b + 1; c <= n; c++)
				for (int d = 1; d <= n; d++) {
					if (mat[a][d] && mat[b][d] && mat[c][d]) {
						for (int e = d + 1; e <= n; e++) {
							if (mat[a][e] && mat[b][e] && mat[c][e]) {
								for (int f = e + 1; f <= n; f++) {
									if (mat[a][f] && mat[b][f] && mat[c][f])
										return false;
								}
							}
						}
					}
				}
	return true;
}

//Uva10768
int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &n, &m)) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (a == b) continue;
			mat[a][b] = mat[b][a] = true;
		}
		printf("%s\n", planarity() ? "YES" : "NO");
	}
	return 0;
}