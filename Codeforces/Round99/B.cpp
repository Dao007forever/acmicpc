#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100000 + 10;
int a[11], b[11], num[11];
int n;
int ret = 0;
int ansx, ansy, ansnum;

void update(int num, int cnt, bool flag, int k) {
	if (cnt + flag + k > ret) {
		ret = cnt + flag + k;
		ansnum = num;
		ansx = flag;
		ansy = k;
	}
}
void output() {
	char s1[MAXN] = {'\0'}, s2[MAXN] = {'\0'};
	if (ansy > 0) {
		for (int i = 0; i < ansy; i++)
			s1[i] = s2[i] = '0';
	}
	a[ansnum]--;
	b[10 - ansnum]--;
	s1[ansy] = '0' + ansnum;
	s2[ansy] = '0' + 10 - ansnum;
	int i = ansy + 1;
	for (;;) {
		bool flag = false;
		for (int j = 1; j < 10; j++) {
			int tmp = min(a[j], b[9 - j]);
			for (int k = 0; k < tmp; k++) {
				flag = true;
				a[j]--;
				b[9 - j]--;
				s1[i] = '0' + j;
				s2[i++] = '0' + 9 - j;
			}
		}
		if (!flag) break;
	}
	if (ansx) {
		for (int j = 1; j < 10; j++)
			if (a[j] && b[10 - j]) {
				s1[i] = '0' + j;
				s2[i++] = '0' + 10 - j;
				break;
			}
	}
	for (int j = 1; j < 10; j++) {
		for (int k = 0; k < a[j]; k++)
			s1[i++] = '0' + j, s2[i++] = '0' + j;
	}
	for (int j = i - 1; j >= 0; j--)
		printf("%c", s1[j]);
	printf("\n");
	for (int j = i - 1; j >= 0; j--)
		printf("%c", s2[j]);
	printf("\n");
}
int main() {
	freopen("in", "r", stdin);
	char str[MAXN];
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++) {
		num[str[i] - '0']++;
		b[str[i] - '0'] = a[str[i] - '0'] = num[str[i] - 'a'];
	}
	for (int i = 1; i < 10; i++) if (a[i] > 0 && b[10 - i] > 0) {
		a[i]--;
		b[10 - i]--;
		int cnt = 1;
		for (int j = 1; j < 10; j++) if (a[i] > 0){
			int tmp = min(a[j], b[9 - j]);
			cnt += tmp;
			a[j] -= tmp; b[9 - j] -= tmp;
		}
		bool flag = false;
		for (int j = 1; j < 10; j++)
			if (a[j] && b[10 - j]) {
				flag = true;
				break;
			}
		update(i, cnt, flag, a[0]);
		for (int j = 0; j < 10; j++)
			a[j] = num[j], b[j] = num[j];
	}
	output();
	return 0;
}
