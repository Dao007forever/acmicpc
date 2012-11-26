/*
 * Author: Yang Zhang
 * Created Time: Mon 03 Sep 2012 10:41:41 AM CST
 * File Name: 3261_RACETIME.cpp
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

#define MAXN 110000
int n, q, numB;
int val[MAXN], ind[MAXN], st[MAXN], ed[MAXN];
vector<int> Blk[MAXN];

int binary(vector<int> &v, int x) {
	if (v[0] > x) return 0;
	int l = 0, r = v.size() - 1, ret;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (v[mid] <= x) {
			ret = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	return ret + 1;
}

int main() {
	scanf("%d%d", &n, &q);
	int sq = sqrt(n);
	numB = 0;
	for (int i = 1, j; i <= n; i += sq) {
		numB++;
		st[numB] = i;
		for (j = i; j < i + sq && j <= n; j++) {
			scanf("%d", &val[j]);
			ind[j] = numB;
			Blk[numB].PB(val[j]);
		}
		ed[numB] = j - 1;
		sort(Blk[numB].begin(), Blk[numB].end());
	}

	for (; q--; ) {
		char op[5];
		scanf("%s", op);
		if (*op == 'M') {
			int a, x, k;
			scanf("%d%d", &a, &x);
			int idx = ind[a], size = Blk[ind[a]].size();
			for (int i = 0; i < size; i++)
				if (Blk[idx][i] == val[a]) {
					k = i;
					break;
				}
			val[a] = x;
			Blk[idx][k] = Blk[idx][size - 1];
			Blk[idx][size - 1] = x;
			sort(Blk[idx].begin(), Blk[idx].end());
		} else if (*op == 'C') {
			int a, b, x;
			scanf("%d%d%d", &a, &b, &x);
			int ret = 0;
			for (int i = ind[a]; i <= ind[b]; i++) {
				if (a <= st[i] && b >= ed[i]) {
					ret += binary(Blk[i], x);
				} else {
					for (int j = max(st[i], a); j <= min(ed[i], b); j++)
						ret += val[j] <= x;
				}
			}
			printf("%d\n", ret);
		}
	}
	/*int a, b, X;
	char op[5];
	 while( q-- ){
        scanf("%s", op);
        if( *op=='M' ){
            scanf("%d%d",&a,&X );
            for(int i=0;i<Blk[ind[a]].size();i++ ){
                if( Blk[ind[a]][i]==val[a] ){
                    break;
                }
            }

            val[a] = X;
            Blk[ind[a]][i] = Blk[ind[a]][Blk[ind[a]].size()-1];
            Blk[ind[a]][Blk[ind[a]].size()-1] = val[a];
            sort( Blk[ind[a]].begin(),Blk[ind[a]].end());
        }
        else if( *op=='C' ){
            scanf("%d%d%d",&a,&b,&X );
            int Ans = 0;
            for(int i=ind[a];i<=ind[b];i++ ){
                if( a<=st[i] && b>=ed[i] ){
                    Ans += binary( Blk[i],X );
                }
                else{
                    for( j=max( st[i],a);j<=min( ed[i],b );j++ ){
                        Ans += val[j]<=X;
                    }
                }
            }
            printf("%d\n",Ans );
        }*/
	return 0;
}

