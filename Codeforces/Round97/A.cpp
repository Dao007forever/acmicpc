#include <cstdio>
#include <algorithm>
using namespace std;

struct Node {
	int a, b, id;
}ps[111111];
int n;

bool cmpa(const Node &A, const Node &B) {
	if (A.a != B.a) return A.a < B.a;
	return A.id < B.id;
}

bool cmpid(const Node &A, const Node &B) {
	return A.id < B.id;
}

int main() {
	scanf("%d", &n);
	int flag = false;
	for (int i = 0; i < n; i++) {
		scanf("%d", &ps[i].a);
		ps[i].id = i;
		if (ps[i].a != 1) flag = true;
	}
	sort(ps, ps + n, cmpa);
	ps[0].b = 1;
	for (int i = 1; i < n; i++)
		ps[i].b = ps[i - 1].a;
	//sort(ps, ps + n, cmpid);
	for (int i = 0; i < n - 1; i++)
		printf("%d ", ps[i].b);
	if (!flag) ps[n-  1].b = 2;
	printf("%d\n", ps[n - 1].b);
	return 0;
}
