#include <cstdio>
#include <cstring>
int a[15333],sum[15333];
int main(){
	freopen("C.in", "r", stdin);
	int n;
	while (scanf("%d",&n)==1){
		int x,y,z;
		memset(a,0,sizeof(a));
		while (scanf("%d%d%d",&x,&y,&z),x>=0){
			a[x]+=z;
			a[y+1]-=z;
		}
		sum[0]=a[0];
		for (int i=1;i<=n;i++)
			sum[i]=a[i]+sum[i-1];
		int maxp=0;
		for (int i=1;i<=n;i++)
			if (sum[i]>sum[maxp])
				maxp=i;
		printf("%d ",maxp);
		maxp=n;
		for (int i=n-1;i>=0;i--)
			if (sum[i]>sum[maxp])
				maxp=i;
		printf("%d\n",maxp);
	}
	return 0;
}
