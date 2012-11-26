const int MAXN = 1000 + 10;
struct Point
{
    double x, y;
    Point operator-(Point &it)
    {
        Point tmp;
        tmp.x = x - it.x;
        tmp.y = y - it.y;
        return tmp;
    }
};
struct Circle
{
    double radis;
    Point center;
};
struct Triangle
{
    Point t[3];
};
Circle c;
Point a[MAXN];

double dist(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double triangleArea(Triangle t)
{
    Point p1, p2;
    p1 = t.t[1] - t.t[0];
    p2 = t.t[2] - t.t[0];
    return fabs(p1.x * p2.y - p1.y * p2.x) / 2;
}

Circle circumcircleOfTriangle(Triangle t)
{
    //三角形的外接圆
    Circle tmp;
    double a, b, c, c1, c2;
    double xA, yA, xB, yB, xC, yC;
    a = dist(t.t[0], t.t[1]);
    b = dist(t.t[1], t.t[2]);
    c = dist(t.t[2], t.t[0]);
    //根据S = a * b * c / R / 4;求半径R
    tmp.radis = a * b * c / triangleArea(t) / 4;

    xA = t.t[0].x, yA = t.t[0].y;
    xB = t.t[1].x, yB = t.t[1].y;
    xC = t.t[2].x, yC = t.t[2].y;
    c1 = (xA * xA + yA * yA - xB * xB - yB * yB) / 2;
    c2 = (xA * xA + yA * yA - xC * xC - yC * yC) / 2;

    tmp.center.x = (c1 * (yA - yC) - c2 * (yA - yB)) / ((xA - xB) * (yA - yC) - (xA - xC) * (yA - yB));
    tmp.center.y = (c1 * (xA - xC) - c2 * (xA - xB)) / ((yA - yB) * (xA - xC) - (yA - yC) * (xA - xB));
    return tmp;
}

Circle MinCircle2(int tce, Triangle ce)
{
    Circle tmp;
    if (tce == 0) tmp.radis = -2;
    else if (tce == 1)
    {
        tmp.center = ce.t[0];
        tmp.radis = 0;
    }
    else if (tce == 2)
    {
        tmp.radis = dist(ce.t[0], ce.t[1]) / 2;
        tmp.center.x = (ce.t[0].x + ce.t[1].x) / 2;
        tmp.center.y = (ce.t[0].y + ce.t[1].y) / 2;
    }
    else if (tce == 3) tmp = circumcircleOfTriangle(ce);
    return tmp;
}


void MinCircle(int n, int tce, Triangle ce)
{
    Point tmp;
    c = MinCircle2(tce, ce);
    if (tce == 3) return;
    for (int i = 1; i <= n; i++)
    {
        if (dist(a[i], c.center) > c.radis)//a[i]表示要包围的点i
        {
            ce.t[tce] = a[i];
            MinCircle(i - 1, tce + 1, ce);
            tmp = a[i];
            for (int j = i; j >= 2; j--)
                a[j] = a[j - 1];
            a[1] = tmp;
        }
    }
}

void solve(int n)
{
    Triangle ce;
    MinCircle(n, 0, ce);
    printf("%.2lf %.2lf %.2lf\n", c.center.x, c.center.y, c.radis);
}

