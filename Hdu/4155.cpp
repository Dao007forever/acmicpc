#include <cstdio>
#include <cstring>

int f[6][6][6][6][6][6], cnt[10];
int i[10];

int sum(int a[]) {
	int ret = 0;
	for (int i = 1; i <= 6; i++) {
		ret += (4 - a[i]) * i;
	}
	return ret;
}

void prepare() {
	for (i[1] = 0; i[1] <= 4; i[1]++)
		for (i[2] = 0; i[2] <= 4; i[2]++)
			for (i[3] = 0; i[3] <= 4; i[3]++)
				for (i[4] = 0; i[4] <= 4; i[4]++)
					for (i[5] = 0; i[5] <= 4; i[5]++)
						for (i[6] = 0; i[6] <= 4; i[6]++) {
							f[i[1]][i[2]][i[3]][i[4]][i[5]][i[6]] = false;
							if (sum(i) > 31) {
								f[i[1]][i[2]][i[3]][i[4]][i[5]][i[6]] = true;
								continue;
							}

							for (int j = 1; j <= 6; j++)
								if (i[j] > 0) {
									bool flag = false;
									i[j]--;
									if (!f[i[1]][i[2]][i[3]][i[4]][i[5]][i[6]])
										flag = true;
									i[j]++;
									if (flag)
										f[i[1]][i[2]][i[3]][i[4]][i[5]][i[6]] = true;
								}
						}
}

int main() {
	prepare();
	freopen("in.txt", "r", stdin);
	char s[55];
	while (scanf("%s", s) != EOF) {
		int n = strlen(s);
		for (int i = 1; i <= 6; i++)
			cnt[i] = 4;
		for (int i = 0; i < n; i++) {
			cnt[s[i] - '0']--;
		}
		if (f[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][cnt[6]]) {
			if (n & 1) printf("%s B\n", s);
			else printf("%s A\n", s);
		} else {
			if (n & 1) printf("%s A\n", s);
			else printf("%s B\n", s);
		}
	}
	return 0;
}
