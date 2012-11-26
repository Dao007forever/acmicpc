#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node {
	char name[111];
	int v, h;
}p[3333];
int n;

bool cmp(Node a, Node b) {
	return a.v > b.v;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s%d", p[i].name, &p[i].v);
	}
	sort(p, p + n, cmp);

	for (int i = 0; i < n; i++)
		p[i].h = i + 1;

	Node tmp = p[0];
	while (tmp.v > 0) {
		int j;
		for (j = 0; j < tmp.v; j++)
			p[j] = p[j + 1];
		p[j] = tmp;
		tmp = p[0];
	}
	for (int i = 0; i < n; i++)
		printf("%s %d\n", p[i].name, p[i].h);
	return 0;
}
