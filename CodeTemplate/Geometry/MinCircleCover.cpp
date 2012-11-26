/*算法：
1. 在点集中任取 3 点 A,B,C。
2. 作一个包含 A,B,C 三点的最小圆,圆周可能通过这 3 点，也可能只通过其中两点,但包含第 3 点.后一种情况圆周上的两点一定是位于圆的一条直
径的两端。
3. 在点集中找出距离第 2 步所建圆圆心最远的 D 点，若 D 点已在圆内或圆周上，则该圆即为所求的圆，算法结束.则，执行第 4 步。
4. 在 A,B,C,D 中选 3 个点,使由它们生成的一个包含这 4 个点的圆为最小，这 3 点成为新的 A,B,C，返回执行第 2 步。若在第 4 步生成的圆的圆周只通过 A,B,C,D 中的两点，则圆周上的两点取成新的 A和B,从另两点中任取一点作为新的 C。

对于一个给定的点集 A，记 MinCircle(A) 为点集 A 的最小外接圆，显然，对于所有的点集情况 A,MinCircle(A) 都是存在且惟一的。需要特别说明的是，当 A 为空集时，MinCircle(A) 为空集，当 A={a}时，MinCircle(A) 圆心坐标为a，半径为 0；
显然，MinCircle(A) 可以由 A 边界上最多三个点确定(当点集 A 中点的个数大于 1 时，有可能两个点确定了 MinCircle(A))，也就是说存在着一个点集B，|B|<=3 且 B 包含于 A，有 MinCircle(B)=MinCircle(A)。所以，如果 a 不属于 B，则 MinCircle(A-{a})=MinCircle(A);
如果 MinCircle(A-{a}) 不等于 MinCircle(A),则 a 属于 B。
所以我们可以从一个空集 R 开始，不断的把题目中给定的点集中的点加入 R ，同时维护 R 的外接圆最小，这样就可以得到解决该题的算法。
*/
const int MAXN = 1000 + 10;
struct Point {
    double x, y;
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    Point operator-(Point &it)
    {
        Point tmp;
        tmp.x = x - it.x;
        tmp.y = y - it.y;
        return tmp;
    }
};
struct Circle {
    double radis;
    Point center;
};
struct Triangle {
    Point t[3];
};
Circle c;
Point a[MAXN];

double dist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double triangleArea(Triangle t) {
    Point p1, p2;
    p1 = t.t[1] - t.t[0];
    p2 = t.t[2] - t.t[0];
    return fabs(p1.x * p2.y - p1.y * p2.x) / 2;
}

Circle circumcircleOfTriangle(Triangle t) {
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

Circle MinCircle2(int tce, Triangle ce) {
    Circle tmp;
    if (tce == 0) tmp.radis = -2;
    else if (tce == 1) {
        tmp.center = ce.t[0];
        tmp.radis = 0;
    }
    else if (tce == 2) {
        tmp.radis = dist(ce.t[0], ce.t[1]) / 2;
        tmp.center.x = (ce.t[0].x + ce.t[1].x) / 2;
        tmp.center.y = (ce.t[0].y + ce.t[1].y) / 2;
    }
    else if (tce == 3) tmp = circumcircleOfTriangle(ce);
    return tmp;
}


void MinCircle(int n, int tce, Triangle ce) {
    Point tmp;
    c = MinCircle2(tce, ce);
    if (tce == 3) return;
    for (int i = 1; i <= n; i++) {
        if (dist(a[i], c.center) > c.radis) {//a[i]表示要包围的点i
            ce.t[tce] = a[i];
            MinCircle(i - 1, tce + 1, ce);
            tmp = a[i];
            for (int j = i; j >= 2; j--)
                a[j] = a[j - 1];
            a[1] = tmp;
        }
    }
}

//下标从1开始
void solve(int n) {
    Triangle ce;
    MinCircle(n, 0, ce);
    printf("%.2lf %.2lf %.2lf\n", c.center.x, c.center.y, c.radis);
}
