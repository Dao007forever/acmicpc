
  /*
    Prob    :  Fixing the Great Wall
    Source  :  CERC2004-F
    Author  :  ChenDanqi, Yali Middle School
  */

  #include <cstdio>
  #include <cstring>
  #include <cmath>
  #include <algorithm>

  using namespace std;

  const int maxN   =  1000 + 5;

  struct node
    {
      int pos, delta;
    }a[maxN];

  int N, V, Robot;
  double Sd[maxN];
  double f[maxN][maxN][2];
  double ans;

  bool cmp(node p, node q)
    {
      return p.pos < q.pos;
    }

  void init()
    {
      ans = 0;
      for (int i = 1; i <= N; i ++)
        {
          int C;
          scanf("%d %d %d", &a[i].pos, &C, &a[i].delta);
          ans += C;
        }
      sort(a + 1, a + N + 1, cmp);
      
      Sd[0] = 0;
      for (int i = 1; i <= N; i ++)
        Sd[i] = Sd[i - 1] + double(a[i].delta) / V;
    }

  void work()
    {

      for (int i = 1; i <= N; i ++)
        for (int j = i; j <= N; j ++) 
          f[i][j][0] = f[i][j][1] = 1e10;

      for (int i = 1; i <= N; i ++) 
        f[i][i][0] = f[i][i][1] = fabs(double(Robot) - a[i].pos) * Sd[N];
        
      for (int i = N; i >= 1; i --)
        for (int j = i; j <= N; j ++)
          for (int k = 0; k <= 1; k ++)
            {
              double x = !k ? a[i].pos : a[j].pos;
              double s = Sd[N] - Sd[j] + Sd[i - 1];
              if (i > 1) f[i - 1][j][0] <?= f[i][j][k] + fabs(x - a[i - 1].pos) * s;
              if (j < N) f[i][j + 1][1] <?= f[i][j][k] + fabs(x - a[j + 1].pos) * s;
            }

       ans += min(f[1][N][0], f[1][N][1]);
       printf("%d\n", int(ans));
    }

  int main()
    {
      while (scanf("%d %d %d", &N, &V, &Robot), N && V && Robot)
        {
          init();
          work();
        }
      return 0;
    }

