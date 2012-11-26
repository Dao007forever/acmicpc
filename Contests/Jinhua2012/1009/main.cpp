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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define maxn 110
#define maxm 1010
const long long inf = 0x3f3f3f3f3f3f3f3fLL;

struct Mat {
    long long m, n;
    long long d[maxm][maxm];	//只能凭感觉取，不能取maxn
    void init(long long m, long long n) {
    	if(m>maxn || n>maxn) {
			while(true);
    	}
    	this->m = m;
    	this->n = n;
    	memset(d, 0, sizeof(d));
    }
    long long det(long long mod)
    {
        long long ans=1;
        for(long long i=0; i<m; i++)
        {
            for(long long j=i+1; j<m; j++)
                while(d[i][j]!=0)
                {
                    long long t=d[i][i]/d[i][j];
                    for(long long k=0; k<n; k++)
                        d[k][i]=(d[k][i]-(t*d[k][j])%mod)%mod;
                    long long temp;
                    for(long long k=0; k<m; k++)
                    {
                        temp=d[k][i];
                        d[k][i]=d[k][j];
                        d[k][j]=temp;
                    }
                    ans=-ans;
                }
            if(d[i][i]==0)
                return 0;
        }
        for(long long i=0; i<n; i++)
            ans=(ans*d[i][i])%mod;
		return (ans%mod+mod)%mod;
        //return ans;
    }
};

struct DS {
	long long * p, * r, n;
	DS(long long n) {
		this->n = n;
		p = new long long[n];
		r = new long long[n];
	}
	void make() {
		memset(r, 0, sizeof(long long)*n);
		memset(p, 255, sizeof(long long)*n);
	}
	long long find(long long x) {
		long long px, i;
		for(px = x; p[px] != -1; px = p[px]);
		while(x != px) {
			i = p[x];
			p[x] = px;
			x = i;
		}
		return px;
	}
	//失败返回-1，否则返回新祖先
	long long unio(long long x, long long y) {
		x = find(x);	y = find(y);
		if(x == y)	return -1;
		if(r[x]>r[y]) {
			p[y]=x;
			return x;
		} else {
			p[x] = y;
			if(r[x] == r[y])	r[y] ++;
			return y;
		}
	}
};

//---------------------华丽的分隔线---------------------
struct Edge {
	long long a, b, v;
	bool operator < (const Edge & edge) const {
		return v < edge.v;
	}
};

long long dealOne(Edge * e, long long num, long long mod) {
	static Mat mat;
	static long long arr[maxm*2];
	long long len = 0;
	for(long long i = 0; i < num; i ++) {
		arr[len ++] = e[i].a;
		arr[len ++] = e[i].b;
	}
	sort(arr, arr+len);
	len = unique(arr, arr+len)-arr;
	mat.init(len-1, len-1);	//N-1主子式
	long long a, b;
	for(long long i = 0; i < num; i ++) {
		a = lower_bound(arr, arr+len, e[i].a) - arr;
		b = lower_bound(arr, arr+len, e[i].b) - arr;
		mat.d[a][b] --;
		mat.d[b][a] --;
		
		mat.d[a][a] ++;
		mat.d[b][b] ++;
	}
	return mat.det(mod);
}

long long compute(Edge * es, long long n, long long m, long long mod) {
	static DS ds(maxn);
	static Edge mark[maxm];
	ds.make();
	sort(es, es+m);
	long long j;
	long long res = 1;
	long long count = 0;
	for(long long i = 0; i < m; i = j) {
		for(j = i; j < m && es[i].v==es[j].v; j ++) {
			mark[j].a = ds.find(es[j].a);
			mark[j].b = ds.find(es[j].b);
		}
		for(j = i; j < m && es[i].v==es[j].v; j ++) {
			if(-1 != ds.unio(es[j].a, es[j].b)) {
				count ++;
			}
		}
		long long bound = j;
		for(j = i; j < m && es[i].v==es[j].v; j ++) {
			if(mark[j].a != mark[j].b) {
				mark[j].v = ds.find(mark[j].a);
			} else {
				mark[j].v = inf;
				bound --;
			}
		}
		sort(mark+i, mark+j);
		long long ii, jj;
		for(ii = i; ii < bound; ii = jj) {
			for(jj = ii; jj < bound && mark[ii].v==mark[jj].v; jj ++);
			res = (res * dealOne(mark+ii, jj-ii, mod)) % mod;
		}
	}
	res = (res%mod+mod) % mod;
	if(count != n-1)	res = 0;
	if(res < 0)	res += mod;
	return res;
}

Edge es[maxm];
long long n, m;

//hdu 4408
int main() {
	int n, m, p;
	while(scanf("%d%d%d", &n, &m, &p), n||m||p) {
		for(long long j = 0; j < m; j ++) {
			int a, b, v;
			scanf("%d%d%d", &a, &b, &v);
			es[j].a = a-1;
			es[j].b = b-1;
			es[j].v = v;
		}
		cout << compute(es, n, m, p) << endl;
	}
	return 0;
}
