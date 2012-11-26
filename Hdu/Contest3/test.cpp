#include <cstdio>  
#include <fstream>  
#include <algorithm>  
using namespace std;  
const int N = 50050;  
int top;  
inline double fabs(double a) {return a > 0 ? a : -a;}  
struct Point  
{  
    double x, y;  
    Point():x(0),y(0){};  
    inline void get() {scanf("%lf%lf", &x, &y);}  
} point[N], center, st[N];  
int tot, buttom;  
void getdata()  
{  
    scanf("%d", &tot);  
    double x, y;  
    x = y = 1e60;  
    for (int i = 0; i < tot; i++)  
    {  
        point[i].get();  
        if (point[i].x < x || point[i].x == x && point[i].y < y)  
        {  
            x = point[i].x;  
            y = point[i].y;  
            buttom = i;  
        }  
    }  
}  
void getcenter()  
{  
    center = Point();  
    Point& c = center;  
    double s = 0, a;  
    for (int i = 0; i < tot - 1; i++)  
    {  
        a = (point[i].x*point[i+1].y - point[i].y*point[i+1].x);  
        s += a;  
        c.x += a*(point[i].x+point[i+1].x);  
        c.y += a*(point[i].y+point[i+1].y);  
    }  
    a = (point[tot-1].x*point[0].y - point[tot-1].y*point[0].x);  
    s += a;  
    c.x += a*(point[tot-1].x+point[0].x);  
    c.y += a*(point[tot-1].y+point[0].y);  
    c.x /= (s*3);  
    c.y /= (s*3);  
   // printf("centre:%lf %lf\n", c.x, c.y);  
}  
inline double mul(const Point& a, const Point& b, const Point& c)  
{  
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);  
}  
inline double dist(const Point& a, const Point& b)  
{  
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);  
}  
bool cmp(const Point &a, const Point &b)  
{  
    double k = mul(point[0], a, b);  
    if (k < 0 || !k && dist(a, point[0]) > dist(b, point[0]))  
        return false;  
    return true;  
}  
void Convex()  
{  
    swap(point[0], point[buttom]);  
    sort(point + 1, point + tot, cmp);  
    top = 2;  
    st[0] = point[0];  
    st[1] = point[1];  
    st[2] = point[2];  
    point[tot] = point[0];  
    for (int i = 3; i <= tot; i++)  
    {  
        while (mul(st[top-1], st[top], point[i]) <= 0 && top >=2) --top;  
        st[++top] = point[i];  
    };  
   // for (int i = 0; i <= top; i++) st[i].print();  
}  
void slove()  
{  
    int ans = 0;  
    double cx, ab, cy;  
    for (int i = 0; i < top; i++)  
    {  
        cx = (st[i+1].x-st[i].x)*(center.x-st[i].x) + (st[i+1].y-st[i].y)*(center.y-st[i].y);  
        cy = (center.x-st[i+1].x)*(st[i].x-st[i+1].x) + (center.y-st[i+1].y)*(st[i].y-st[i+1].y);  
     //   printf("cx:%lf ab:%lf %lf %lf %lf %lf\n", cx, ab, st[i].x, st[i].y, st[i+1].x, st[i+1].y);  
        if (cx > 0 && cy > 0)  
        {  
            ans++;  
        }  
    }  
    printf("%d\n", ans);  
}  
int main()  
{  
    freopen("a", "r", stdin);  
    int n; scanf("%d", &n);  
    while (n--)  
    {  
        getdata();  
        getcenter();  
        Convex();  
        slove();  
    }  
}  
