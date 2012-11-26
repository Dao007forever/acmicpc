#include <cstdio>
#include <queue>
using namespace std;

struct node {
	int a, b, d;
};
queue<node> Q;
int n;

int main() {
	//freopen("in", "r", stdin);
	scanf("%d", &n);
	node tmp;
	tmp.a = 1, tmp.b = 1;
	tmp.d = 0;
	Q.push(tmp);
	while (!Q.empty()) {
		node cur = Q.front();
		Q.pop();
		if (cur.a == n || cur.b == n) {
			printf("%d\n", cur.d);
			return 0;
		}
		tmp.a = cur.a, tmp.b = cur.b + cur.a;
		tmp.d = cur.d + 1;
		Q.push(tmp);
		tmp.a = cur.a + cur.b, tmp.b = cur.b;
		tmp.d = cur.d + 1;
		Q.push(tmp);
	}
	return 0;
}
