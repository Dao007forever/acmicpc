#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int w, l, h;
}p[555];
int n;
int adj[555][555], cx[555], cy[555], mk[555];

bool contain(node A, node B) {
	return (A.w > B.w) && (A.l > B.l) && (A.h > B.h);
}

bool path(int i)
{
    for (int j = 0; j < n; j++)
    {
        if (adj[i][j] && !mk[j])
        {
            mk[j] = true;
            if (cy[j] == -1 || path(cy[j]))
            {
                cx[i] = j;
                cy[j] = i;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        memset(mk, 0, sizeof(mk));
        if (path(i)) res++;
    }
    return res;
}

int main() {
	freopen("in", "r", stdin);
	while (cin >> n && n) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++) {
			cin >> p[i].w >> p[i].l >> p[i].h;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (contain(p[i], p[j])) adj[i][j] = 1;
		int ret = MaxMatch();
		cout << n - ret << endl;
	}
	return 0;
}
