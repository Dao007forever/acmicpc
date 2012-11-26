/*
 * Author: Yang Zhang
 * Created Time: Fri 24 Aug 2012 09:12:55 PM CST
 * File Name: 2853.cpp
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

const int inf = 0x3f3f3f3f;
#define MAXN 105
struct KM {
	int E[MAXN][MAXN], n;		//图的所在，需传入
	bool map[MAXN][MAXN];		//每次二分匹配时的图
	
	bool visx[MAXN], visy[MAXN];//判断二分匹配时,某点是否在交错树上
	int mate[MAXN];				//V2中某点的伙伴，-1为空
	
	bool dfs(int idx) {
		visx[idx] = true;
		for(int i = 0; i < n; i ++) {
			if(map[idx][i] && !visy[i]) {
				visy[i] = true;
				if(mate[i]==-1 || dfs(mate[i])) {
					mate[i] = idx;
					return true;
				}
			}
		}
		return false;
	}
	int solve() {
		static int lx[MAXN], ly[MAXN];//V1和V2中点的标号
		int i, j;
		for(i = 0; i < n; i ++) {
			ly[i] = 0;
			lx[i] = -inf;
			for(j = 0; j < n; j ++) {
				lx[i] = max(lx[i], E[i][j]);
			}
		}
		while(true) {
			for(i = 0; i < n; i ++) {
				for(j = 0; j < n; j ++) {
					map[i][j] = lx[i]+ly[j]==E[i][j];
				}
			}
			//构图完毕，开始二分匹配
			memset(mate, 255, sizeof(mate));
			for(i = 0; i < n; i ++) {
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if(false == dfs(i))	break;
			}
			if(i == n) {	//找到完备匹配
				break;
			} else {		//未找到完备匹配，修改标号
				int ex = inf;
				for(i = 0; i < n; i ++) {
					if(false == visx[i])	continue;
					for(j = 0; j < n; j ++) {
						if(false == visy[j])
							ex = min(ex, lx[i]+ly[j]-E[i][j]);
					}
				}
				for(i = 0; i < n; i ++) {
					if(visx[i])	lx[i] -= ex;
					if(visy[i])	ly[i] += ex;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++) {
			ans += E[mate[i]][i];
		}
		return ans;
	}
}km;
int n, m, K = 55;
int e[55][55];
int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(km.E, 0, sizeof(km.E));
		km.n = m;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &e[i][j]);
				km.E[i][j] = e[i][j] * K;
			}
		}
		int sum = 0;
		for (int i = 0, j; i < n; i++) {
			scanf("%d", &j); j--;
			km.E[i][j]++;
			sum += e[i][j];
		}
		int ret = km.solve();
		int cnt = ret % K;
		printf("%d %d\n", n - cnt, ret / K - sum);
	}
	return 0;
}

