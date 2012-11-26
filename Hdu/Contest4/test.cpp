#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
#define maxn 100
#define inf 100000000
int dp[maxn];
int re[maxn][maxn];
int main()
{
    int T,n,i,j,m,k;
    freopen("in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int a,b;
        for(i=1;i<=n;i++)
        {
            scanf("%d%d",&a,&b);
            dp[a]=b-1;
        }
        scanf("%d",&m);
        for(i=1;i<=n;i++)for(j=1;j<=n;j++)re[i][j]=inf;
for(i=1;i<=n;i++)for(j=1;j<=n;j++)if(dp[i]==dp[j])re[i][j]=0;
        for(i=1;i<=m;i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            re[a][b]=c;
        }

        for(k=1;k<=n;k++)for(i=1;i<=n;i++) for(j=1;j<=n;j++)
if(re[i][j]>re[i][k]+re[k][j])
                        re[i][j]=re[i][k]+re[k][j];
        for(i=1;i<=n;i++) for(j=1;j<=n;j++)
                if(dp[i]>dp[j]+re[j][i])
               dp[i]=dp[j]+re[j][i];
                
            
            
        for(i=1;i<=n;i++)
            printf("%d %d\n",i,dp[i]);

        int ans=0;
        for(i=1;i<=n;i++)
        {
            bool flag=1;
            for(j=1;j<=n;j++)
            {
                for(k=1;k<=n;k++)
                {
                    if(i==j||i==k||k==j)continue;
                    if(dp[i]==dp[j]+dp[k])
                    {
                        ans++;
                        flag=0;
                        break;
                    }
                }
                if(flag==0)break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
