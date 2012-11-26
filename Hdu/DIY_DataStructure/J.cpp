/*
 * Author : Yang Zhang
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

const int MAXN = 1000000 + 10;
const int INF = 100000000;
int N , K;
int head , tail;
int a[MAXN];
int id[MAXN], que[MAXN];

bool empty()
{
	if (head <= tail) return 0;
	else return 1;
}
vector<int> ans;
int main()
{
	while (scanf("%d%d" , &N , &K) != EOF) {
		for (int i = 1 ; i <= N ; i++)
			scanf("%d" , &a[i]);
		for (int i = 0 ; i <= N ; i++)
			que[i] = INF;
		ans.clear();
		head = 1;
		tail = 0;
		for (int i = 1 ; i <= N ; i++) {
			while (i - id[head] + 1 > K && !empty())
				head++;
			while (! empty() && a[i] <= que[tail])
				tail--;
			que[++tail] = a[i];
			if (i >= K) {
//				printf("%d " , que[head]);
				ans.PB(que[head]);
			}
			id[tail] = i;
		}
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
//		printf("\n");
		for (int i = 0 ; i <= N ; i++)
			que[i] = -INF;
		for (int i = 0 ; i <= N ; i++)
			id[i] = 0;
		ans.clear();
		head = 1;
		tail = 0;
		for (int i = 1 ; i <= N ; i++) {
			while (i - id[head] +  1 > K && !empty())
				head++;
			while (! empty() && a[i] >= que[tail])
				tail--;
			que[++tail] = a[i];
			if (i >= K) {
//				printf("%d " , que[head]);
				ans.PB(que[head]);
			}
			id[tail] = i;
		}
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
//		printf("\n");
	}
	return 0;
}
