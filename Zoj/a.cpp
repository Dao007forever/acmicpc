#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std ;

const int MaxSize=100000+2 ;
struct Point{
    double x, y ;
} ;
Point point[MaxSize], *px[MaxSize], *py[MaxSize] ;

inline double dis( Point *a, Point *b )
{
    return sqrt( (a->x-b->x)*(a->x-b->x) + (a->y-b->y)*(a->y-b->y) ) ;
}

// 下面的这个函数很有意思，就是给出两条边，求出以这两条边为直角边的三角形的斜边。
// 正好可以用来求两个点之间的距离。 
/*inline double dis( Point *a, Point *b )
{
    return hypot( a->x - b->x, a->y - b->y ) ;
}*/

bool cmpx( Point *p1, Point *p2 )
{
    return p1->x < p2->x ;
}

bool cmpy( Point *p1, Point *p2 )
{
    return p1->y < p2->y ;
}

// 如果不用自己写的内联函数，效率只会差那么一点点，我只是为了娱乐，才自己写了一个。 
inline double min( double a, double b )
{
    return a<b ? a:b ;
}

double closest( int l, int r )
{
    if( l+1 == r )
        return dis( px[l], px[r]  ) ;
    if( l+2 == r )
        return min( dis(px[l],px[l+1]), min( dis(px[l+1],px[r]), dis(px[l],px[r]) ) ) ;
    
    int mid = (l+r)/2 ;
    double ans = min( closest(l,mid), closest(mid+1,r) ) ;
    int i, j, cnt=0 ;
    for( i=l; i<=r; ++i ){
        if( px[i]->x >= px[mid]->x-ans && px[i]->x <= px[mid]->x+ans ){
            py[cnt++] = px[i] ;
        }
    }
    sort( py, py+cnt, cmpy ) ;
    for( i=0; i<cnt; ++i ){
        for( j=i+1; j<cnt; ++j ){
            // py数组中的点是按照y坐标升序的 
            if( py[j]->y - py[i]->y >= ans )
                break ;
            ans = min( ans, dis(py[i],py[j]) ) ;
        }
    }
    return ans ;
}

int main()
{
	freopen("a", "r", stdin);
    int i, n ;
    while( scanf("%d", &n), n ){
        for( i=0; i<n; ++i ){
            scanf("%lf%lf", &point[i].x, &point[i].y ) ;
            px[i] = &point[i] ;
        }
        sort( px, px+n, cmpx ) ;
        double distance = closest( 0, n-1 ) ;
        printf("%.2lf\n", distance/2.0 ) ;
    }
    return 0 ;
}
