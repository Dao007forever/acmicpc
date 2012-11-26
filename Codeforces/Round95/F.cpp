#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int N, M, K;
char str[555][555];
int map[555][555], sum[555][555];

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < N; i++) 
		scanf("%s", str[i]);
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < M - 1; j++)
			if (str[i][j] == '1' && str[i - 1][j] == '1' && str[i + 1][j] == '1' && str[i][j - 1] == '1' && str[i][j + 1] == '1')
				map[i][j] = 1;
	N -= 2; M -= 2;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			sum[i][j] = sum[i][j - 1] + map[i][j];
	int l1 = 0, l2 = 0;
	long long ret = 0;
	for (int i = 1, cnt; i <= M; i++)
		for (int j = i; j <= M; j++) {
			l1 = l2 = 1;
			cnt = 0;
			for (; l2 <= N; l2++) {
				cnt += sum[l2][j] - sum[l2][i - 1];
				while (cnt >= K) {
					ret += N - l2 + 1;
					cnt -= sum[l1][j] - sum[l1][i - 1];
					l1++;
				}
			}
		}
	cout << ret << endl;
	return 0;
}
