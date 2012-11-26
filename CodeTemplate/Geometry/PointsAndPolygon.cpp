#define maxn 10010
#define M_PI		3.14159265358979323846	/* pi */
double my_sqrt(double d) {return sqrt(max(d, 0.0));}
double my_acos(double d) {return acos(d<-1?-1:d>1?1:d);}
#define sqr(v) ((v)*(v))
const double eps = 1E-6;
int sig(double d) {
	return (d>eps) - (d<-eps);
}
struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point() {}
	Point operator - (const Point & p) const {
		return Point(x-p.x, y-p.y);
	}
	Point operator + (const Point & p) const {
		return Point(x+p.x, y+p.y);
	}
	Point operator * (double d) const {
		return Point(x*d, y*d);
	}
	/*double operator * (const Point &b) const {
		return x * b.y - y * b.x;
	}*/
	bool operator == (const Point & p) const {
		return sig(x-p.x)==0 && sig(y-p.y)==0;
	}
	bool operator < (const Point & p) const {
		return sig(x-p.x)!=0 ? x<p.x : sig(y-p.y)<0;
	}
	Point resize(double d) {
		d /= my_sqrt(sqr(x)+sqr(y));
		return Point(x*d, y*d);
	}
	Point left90() {
		return Point(-y, x);
	}
	Point rotate(double radian) {	//逆时针转
		double c = cos(radian), s = sin(radian);
		return Point(x*c-y*s, y*c+x*s);
	}
	double mod() {
		return my_sqrt(sqr(x)+sqr(y));
	}
	void output() {
		printf("x = %.2f, y = %.2f\n", x, y);
	}
};
double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}
double dot(Point o, Point a, Point b) {
	return (a.x-o.x)*(b.x-o.x) + (a.y-o.y)*(b.y-o.y);
}
double dis(Point a, Point b) {
	return my_sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}
int lineCross(Point a, Point b, Point c, Point d, Point &p) {
	double s1, s2;
	s1=cross(a,b,c);
	s2=cross(a,b,d);
	if(sig(s1)==0 && sig(s2)==0)	return 2;
	if(sig(s2-s1)==0)	return 0;
	p.x = (c.x*s2-d.x*s1)/(s2-s1);
	p.y = (c.y*s2-d.y*s1)/(s2-s1); 
	return 1;
}
double area(Point * p, int n) {
	double res = 0;
	p[n] = p[0];
	for(int i = 0; i < n; i ++) {
		res += p[i].x*p[i+1].y - p[i+1].x*p[i].y;
	}
	return res / 2;
}
//在ax+by+c=0直线上找两个点p1、p2，并且使得向量(p1,p2)的左面为ax+by+c<0一面
//返回ax+by+c是否为一直线，即a^2+b^2 != 0
bool axis(double a, double b, double c, Point & p1, Point & p2) {
	double d = a*a+b*b;
	if(sig(d) > 0) {
		p1 = Point(-a*c/d, -b*c/d);
		p2 = p1 + Point(-b, a);
		return true;
	}
	return false;
}
//下面是新的基本操作
//返回点o到直线ab的距离，res保存o在ab上的投影
double pointToLine(Point o, Point a, Point b, Point & res) {
	double d = dis(a, b);
	double s = cross(a, b, o) / d;
	res = o + (a-b).left90()*(s/d);
	return fabs(s);
}
//oa围绕o点，逆时针转到ob，所转的角度。返回值在(-pi, pi]之间
double angle(Point o, Point a, Point b) {
	double cr = cross(o, a, b);
	double dt = dot(o, a, b);
	if(sig(cr)==0)	cr = 0;
	if(sig(dt)==0)	dt = 0;
	return atan2(cr, dt);
}
/**
 * a1a2逆时针绕点转到b1b2，绕的点为p，转的角度为ang (-pi, pi]
 * 返回：可以转true，不可以转false	当且仅当两向量平行且同向时无解！
 * assume |a1a2| = |b1b2|
 */
bool angle(Point a1, Point a2, Point b1, Point b2, Point & p, double & ang) {
	Point vecA = a2-a1, vecB = b2-b1;
	if(sig(vecA.mod()-vecB.mod()) != 0)	return false;
	
	double cr = vecA.x*vecB.y-vecA.y*vecB.x;
	double dt = vecA.x*vecB.x+vecA.y*vecB.y;
	
	if(sig(cr)==0)	cr = 0;
	if(sig(dt)==0)	dt = 0;
	
	ang = atan2(cr, dt);
	
	if(sig(cr)==0) {
		if(sig(dt)>=0)	return false;
		p = (a1+b1) * 0.5;
		return true;
	}
	Point m1 = (a1+b1)*0.5, m2 = (a2+b2)*0.5;
	if(1!=lineCross(m1, m1+(a1-b1).left90(), m2, m2+(a2-b2).left90(), p))//中垂线交点
		lineCross(a1, a2, b1, b2, p);	//中垂线平行，现在assume 八字型
	return true;
}
//判断p是否在线段ab上，在端点处也返回true
bool onSeg(Point p, Point a, Point b) {
	return sig(cross(p, a, b))==0 && sig(dot(p, a, b))<=0;
}
//---------上面是基本函数-----------
//---------下面是新函数-----------
//判断一个多边形是否是凸多边形，初始为瞬时针、逆时针均可！
bool isConvex(Point * ps, int n) {
	bool s[3] = {1, 1, 1};
	ps[n] = ps[0];
	ps[n+1] = ps[1];
	for(int i = 0; i < n && (s[0] | s[2]); i ++) {
		s[ 1+sig(cross(ps[i+1], ps[i+2], ps[i])) ] = 0;
	}
	return (s[0] | s[2]);			//允许三点共线
	return (s[1] && s[0] | s[2]);	//不允许三点共线, 要用这个for的条件最好也改...
}
//0不在里面	2在里面 1边上
int inside_convex(Point * ps, int n, Point q) {
	bool s[3] = {1, 1, 1};
	ps[n] = ps[0];
	for(int i = 0; i < n && (s[0] | s[2]); i ++) {
		s[ 1+sig(cross(ps[i+1], q, ps[i])) ] = 0;
	}
	if(s[0] | s[2])	return s[1]+1;	//里面或者边上
	return 0;
}
/**
 * 判断点是否在凸多边形内O(n)初始化，log(n)效率，assume多边形为convex并且没有三点共线
 * 教程：http://hi.baidu.com/aekdycoin/blog/item/7abf85026f0d7e85d43f7cfe.html
 * 题目：http://acm.sgu.ru/problem.php?contest=0&problem=253
 */
Point ps[maxn];
double ang[maxn];
int n;
void init() {
	if(area(ps, n) < 0)	reverse(ps, ps+n);
	rotate(ps, min_element(ps, ps+n), ps+n);
	for(int i = 1; i < n; i ++) {
		ang[i] = atan2(ps[i].y-ps[0].y, ps[i].x-ps[0].x);
	}
	ang[0] = -M_PI/2;
}
bool dcmp(double a, double b) {
	return sig(a-b) < 0;
}
//0 外 2 内 1 边上
int judge(Point p) {
	if(onSeg(p, ps[0], ps[1]) || onSeg(p, ps[0], ps[n-1]))	return 1;
	int idx = lower_bound(ang, ang+n, atan2(p.y-ps[0].y, p.x-ps[0].x), dcmp) - ang;
	if(idx <= 1 || idx == n)	return 0;	//外面！
	return 1 + sig(cross(ps[idx-1], ps[idx], p));
}
/*sgu 253，快速判断点是否在凸多边形内
	int main() {
		int m, k;
		while(scanf("%d%d%d", &n, &m, &k) != EOF) {
			for(int i = 0; i < n; i ++)	scanf("%lf%lf", &ps[i].x, &ps[i].y);
			init();
			int sum = 0;
			Point p;
			while(m --) {
				scanf("%lf%lf", &p.x, &p.y);
				if(judge(p)) sum ++;
			}
			if(sum >= k) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
		return 0;
	}
*/
/**
 * 判断点p是否在任意多边形ps中
 * 0外，1内，2边上
 */
int inPolygon(Point * ps, int n, Point p) {
	int cnt = 0;
	ps[n] = ps[0];
	for(int i = 0; i < n; i ++) {
		if(onSeg(p, ps[i], ps[i+1]))	return 2;
		int k = sig( cross(ps[i], ps[i+1], p) );
		int d1 = sig( ps[i+0].y-p.y );
		int d2 = sig( ps[i+1].y-p.y );
		if(k>0 && d1<=0 && d2>0)	cnt ++;
		if(k<0 && d2<=0 && d1>0)	cnt --;
	}
	return cnt != 0;
}
//多边形切割
//用直线ab切割多边形p，切割后的在向量(a,b)的左侧，并原地保存切割结果
//如果退化为一个点，也会返回去, 此时n为1
void polygon_cut(Point * p, int & n, Point a, Point b) {
	static Point pp[maxn];
	int m = 0;
	p[n] = p[0];
	for(int i = 0; i < n; i ++) {
		if(sig(cross(a, b, p[i])) > 0)
			pp[m ++] = p[i];
		if(sig(cross(a, b, p[i])) != sig(cross(a, b, p[i+1])))
			lineCross(a, b, p[i], p[i+1], pp[m ++]);
	}
	n = 0;
	for(int i = 0; i < m; i ++)
		if(!i || !(pp[i]==pp[i-1]))
			p[n ++] = pp[i];
	while(n>1 && p[n-1]==p[0])	n --;
}
//多边形求核，类似于zzy的calCore
const double BOUND = 10000000.0;
bool calCore(Point * p, int & n) {
	static Point pp[maxn];
	if(sig(area(p, n)) >= 0)	copy(p, p+n, pp);
	else				reverse_copy(p, p+n, pp);
	pp[n] = pp[0];
	int nn = n;			//pp,nn init over!
	
	p[0] = Point(-BOUND, -BOUND);
	p[1] = Point(BOUND, -BOUND);
	p[2] = Point(BOUND, BOUND);
	p[3] = Point(-BOUND, BOUND);
	n = 4;				//p, n init over!
	
	for(int i = 0; i < nn && n; i ++)
		polygon_cut(p, n, pp[i], pp[i+1]);
	return n != 0;
}
/**求最近点对，分两个版本：
 * 1.	【版本1】：将靠近中心线的点按照y进行排序，每次递归都进行sort操作。。【类似吉大】
 *		算法效率n^n logn，但是实际效果可能更好一些！
 * 2.	【版本2】：将所有的点按照y进行归并排序，每次递归进行inplace_merge操作。【类似上交】
 * 		算法效率nlogn，但是纯的nlogn，实际效果不一定最好。。。
 * 3.	【求集合间的最近点对】
 *类似poj3714，如果有两个点集，求点集间的最短距离，只需给Point加id域，且在close0的倒数第二行：
 *	res = min(res, dis(psy[i], psy[j]));
 *的前面加一个if语句就可以了，比如
 *	if(psy[i].id^psy[j].id)
 *		res = min(res, dis(psy[i], psy[j]));
 *并且用【版本2】的模板速度会快一点！！！
 */
bool cmp_x(const Point & a, const Point & b) {return a.x<b.x;}
bool cmp_y(const Point & a, const Point & b) {return a.y<b.y;}
//【版本1】：将靠近中心线的点按照y进行排序，每次递归都进行sort操作。。【类似吉大】
//算法效率n^n logn，但是实际效果可能更好一些！
double close0(Point * ps, int l, int r) {
	static Point psy[maxn];
	if(r-l <= 1)    return 1E100;
	int m = (l + r) / 2, i;
	double res = 1E100;
	for(i = m; i >= l && sig(ps[i].x-ps[m].x)==0; i --);
    res = min(res, close0(ps, l, i+1));
	for(i = m; i < r  && sig(ps[i].x-ps[m].x)==0; i ++);
    res = min(res, close0(ps, i, r));
	int len = 0;
	for(i = m;   i>= l && sig(ps[m].x-res-ps[i].x)<0; i --)   psy[len ++] = ps[i];
	for(i = m+1; i < r && sig(ps[m].x+res-ps[i].x)>0; i ++)   psy[len ++] = ps[i];
	sort(psy, psy+len, cmp_y);
	for(int i = 0; i < len; i ++)
		for(int j = i+1; j<len && psy[j].y<psy[i].y+res; j ++)
			res = min(res, dis(psy[i], psy[j]));
    return res;
}
double close(Point * ps, int n) {
	sort(ps, ps+n, cmp_x);
	return close0(ps, 0, n);
}
//【版本2】：将所有的点按照y进行归并排序，每次递归进行inplace_merge操作。【类似上交】
//算法效率nlogn，但是纯的nlogn，实际效果不一定最好。。。
double close0_(Point * ps, int l, int r) {
	static Point psy[maxn];
	if(r-l <= 1)	return 1E300;
	int m = (l + r) / 2;
	double midX = ps[m].x;
	double res = min( close0_(ps, l, m), close0_(ps, m, r) );
	inplace_merge(ps+l, ps+m, ps+r, cmp_y);
	double x1 = midX-res, x2 = midX+res;
	int len = 0;
	for(int i = l; i < r; i ++)
		if(sig(x1-ps[i].x)<0 && sig(ps[i].x-x2)<0)
			psy[len ++] = ps[i];
	for(int i = 0; i < len; i ++)
		for(int j = i+1; j<len && psy[j].y<psy[i].y + res; j ++)
			res = min(res, dis(psy[i], psy[j]));
	return res;
}
double close_(Point * ps, int n) {
	sort(ps, ps+n, cmp_x);
	return close0_(ps, 0, n);
}
/**
 * 下面开始【【【【【【旋转卡壳】】】】】】】！！！
 * 旋转卡壳全集教程：http://blog.csdn.net/ACMaker/archive/2008/10/29/3176910.aspx
 */
/**
 * 求凸多边形直径！注意传入凸多边形！
 */
double diam(Point *p, int n) {
	if(area(p, n)<0)	reverse(p, p+n);
	p[n] = p[0];
	double res = 0;
	for(int i = 0, j = 1; i < n; i ++) {
		while(sig(cross(p[i], p[i+1], p[j])-cross(p[i], p[i+1], p[(j+1)%n])) < 0)
			j = (j+1)%n;
		res = max(res, dis(p[i], p[j]));
		res = max(res, dis(p[i+1], p[j]));
	}
	return res;
}
//计算两个凸多边形间最近，最远距离，assume两个凸多边形分离
//返回o到线段ab的最短距离
double minDis(Point o, Point a, Point b) {
	if(sig(dot(b, a, o))<0)	return dis(o, b);
	if(sig(dot(a, b, o))<0)	return dis(o, a);
	return fabs(cross(o, a, b)/dis(a, b));
}
//计算从curAng逆时针转到ab的角
double calRotate(Point a, Point b, double curAng) {
	double x = fmod(atan2(b.y-a.y, b.x-a.x)-curAng, M_PI*2);
	if(x<0)			x += M_PI*2;
	if(x>1.9*M_PI)	x = 0;		//in case x is nearly 2*M_PI
	if(x >= 1.01*M_PI)	while(1);
	return x;
}
//求凸多边形间最小距离，断言P和Q分离
//传入P、Q：凸多边形。n、m：P和Q的顶点个数
//如果P和Q非逆时针，则reverse!
//题目：POJ-3608
//教程：http://blog.csdn.net/ACMaker/archive/2008/10/29/3178696.aspx
double mind2p(Point *P, int n, Point *Q, int m) {
	if(area(P, n) < 0)	reverse(P, P+n);	//需要逆时针的
	if(area(Q, m) < 0)	reverse(Q, Q+m);
	int p0 = min_element(P, P+n)-P, q0 = max_element(Q, Q+m)-Q;
	
	double res = dis(P[p0], Q[q0]);
	
	double ang = -M_PI/2, rotateP, rotateQ;
	int pi, pj, qi, qj, totP, totQ, val;
	for(pi=p0, qi=q0, totP=0, totQ=0; totP<n && totQ<m; ) {
		pj = (pi+1) % n;
		qj = (qi+1) % m;
		
		rotateP = calRotate(P[pi], P[pj], ang);
		rotateQ = calRotate(Q[qi], Q[qj], ang+M_PI);
		
		val = sig(rotateP - rotateQ);
		ang += min(rotateP, rotateQ);
		
		if(val == -1)	res = min(res, minDis(Q[qi], P[pi], P[pj]));
		else if(val==1)	res = min(res, minDis(P[pi], Q[qi], Q[qj]));
		else {
			res = min(res, minDis(P[pi], Q[qi], Q[qj]));
			res = min(res, minDis(P[pj], Q[qi], Q[qj]));
			res = min(res, minDis(Q[qi], P[pi], P[pj]));
			res = min(res, minDis(Q[qj], P[pi], P[pj]));
		}
		if(val != 1)	pi=pj, totP ++;
		if(val != -1)	qi=qj, totQ ++;
	}
	return res;
}
//求凸多边形间最大距离，断言P和Q分离
//传入P、Q：凸多边形。n、m：P和Q的顶点个数
//如果P和Q非逆时针，则reverse!
//教程：http://blog.csdn.net/ACMaker/archive/2008/10/29/3178794.aspx
double maxd2p(Point *P, int n, Point *Q, int m) {	//【【【待测】】】.......!!!
	if(area(P, n) < 0)	reverse(P, P+n);	//需要逆时针的
	if(area(Q, m) < 0)	reverse(Q, Q+m);
	int p0 = min_element(P, P+n)-P, q0 = max_element(Q, Q+m)-Q;
	
	double res = dis(P[p0], Q[q0]);
	
	double ang = -M_PI/2, rotateP, rotateQ;
	int pi, pj, qi, qj, totP, totQ, val;
	for(pi=p0, qi=q0, totP=0, totQ=0; totP<n && totQ<m; ) {
		pj = (pi+1) % n;
		qj = (qi+1) % m;
		
		rotateP = calRotate(P[pi], P[pj], ang);
		rotateQ = calRotate(Q[qi], Q[qj], ang+M_PI);
		
		val = sig(rotateP - rotateQ);
		ang += min(rotateP, rotateQ);
		
		if(val == -1)	res = max(res, max(dis(Q[qi], P[pi]), dis(Q[qi], P[pj])));
		else if(val==1)	res = max(res, max(dis(P[pi], Q[qi]), dis(P[pi], Q[qj])));
		else {
			res = max(res, dis(P[pi], Q[qi]));
			res = max(res, dis(P[pi], Q[qj]));
			res = max(res, dis(P[pj], Q[qi]));
			res = max(res, dis(P[pj], Q[qj]));
		}
		if(val != 1)	pi=pj, totP ++;
		if(val != -1)	qi=qj, totQ ++;
	}
	return res;
}
/**
//poj3608
	Point P[maxn], Q[maxn];
	int n, m;
	
	int main() {
		while(scanf("%d%d", &n, &m), n||m) {
			for(int i = 0; i < n; i ++)	scanf("%lf%lf", &P[i].x, &P[i].y);
			for(int i = 0; i < m; i ++)	scanf("%lf%lf", &Q[i].x, &Q[i].y);
			printf("%.5f\n", mind2p(P, n, Q, m));
		}
		return 0;
	}
 */
/**
 * 计算凸多边形的最小外接矩形面积
 * 如果要计算点集的最小外接矩形，先求凸包
 * 点集的最小面积/周长外接矩形，UVA10173
 * 教程：http://blog.csdn.net/ACMaker/archive/2008/10/30/3188123.aspx
 */
/**
 * graham求凸包-水平序，结果是按照瞬时针给出的
 */
int graham(Point*p, int n, int*ch) {
#define push(x)     ch[len ++]=x
#define pop()		len --
	sort(p, p+n);
	int len = 0, len0 = 1, i;
	for(i = 0; i < n; i ++) {
		while(len > len0 && sig(cross(p[ch[len-1]], p[ch[len-2]], p[i]))<=0)
			pop();
		push(i);
	}
	len0 = len;
	for(i = n-2; i >= 0; i --) {
		while(len > len0 && sig(cross(p[ch[len-1]], p[ch[len-2]], p[i]))<=0)
			pop();
		push(i);
	}
	return len-1;
}
bool cmp2(const Point &a, const Point &b) {
	return sig(a.y-b.y)!=0 ? a.y<b.y : sig(a.x-b.x)>0;
}
//计算凸多边形的最小外接矩形面积
double minRect0(Point *p, int n) {
	if(n<=2)	return 0;
	if(area(p, n) < 0)	reverse(p, p+n);
	
	int ai = min_element(p, p+n)      -p;
	int bi = min_element(p, p+n, cmp2)-p;
	int ci = max_element(p, p+n)      -p;
	int di = max_element(p, p+n, cmp2)-p;
	int aj, bj, cj, dj;
	
	double res = 1E100, ang = -M_PI/2;
	double ra, rb, rc, rd, r, s, c, ac, bd;
	
	while(ang < M_PI * 0.51) {
		aj=(ai+1)%n;	ra = calRotate(p[ai], p[aj], ang);
		bj=(bi+1)%n;	rb = calRotate(p[bi], p[bj], ang+0.5*M_PI);
		cj=(ci+1)%n;	rc = calRotate(p[ci], p[cj], ang+1.0*M_PI);
		dj=(di+1)%n;	rd = calRotate(p[di], p[dj], ang+1.5*M_PI);
		r = min(min(ra,rb), min(rc,rd));
		ang += r;
		
		s = sin(ang), c = cos(ang);
		
		ac = -s*(p[ci].x-p[ai].x) + c*(p[ci].y-p[ai].y);
		bd =  c*(p[di].x-p[bi].x) + s*(p[di].y-p[bi].y);
		
		res = min(res, fabs(ac*bd));
			//改为(fabs(ac)+fabs(bd))*2就是求最小周长外接矩形
		
		if(sig(ra-r)==0)	ai=aj;
		if(sig(rb-r)==0)	bi=bj;
		if(sig(rc-r)==0)	ci=cj;
		if(sig(rd-r)==0)	di=dj;
	}
	return res==1E100 ? 0 : res;
}
//计算点集的最小外接举行面积，底层调用minRect0
double minRect(Point *p, int n) {
	static Point q[maxn];
	static int ch[maxn];
	int len = graham(p, n, ch);
	for(int i = 0; i < len; i ++)	q[i] = p[ch[len-1-i]];
	return minRect0(q, len);
}
/*
//UVA10173
	Point P[maxn];
	int n;
	int main() {
		while(scanf("%d", &n), n) {
			for(int i = 0; i < n; i ++)	scanf("%lf%lf", &P[i].x, &P[i].y);
			printf("%.4f\n", minRect(P, n));
		}
		return 0;
	}
*/
/**
 * 计算最多共线的点的个数(必须是整点，不能有重点，效率n^2),不能有重点!!
 */
typedef pair<int,int> T;
int gcd(int a, int b) {
	for(int t; t=b; b=a%b, a=t);
	return a;
}
int calNumLine(T *ts, int n) {
	static T tmp[maxn];
	int res = 0;
	int i, j, k;
	for(i = 0; i < n; i ++) {
		for(j = 0; j < i; j ++) {
			int dx = ts[j].first - ts[i].first;
			int dy = ts[j].second-ts[i].second;
			int g = gcd(dx, dy);
			dx /= g;	dy /= g;
			if(dx<0)	dx=-dx,dy=-dy;
			tmp[j] = T(dx, dy);
		}
		sort(tmp, tmp+j);
		for(j = 0; j < i; j = k) {
			for(k = j; k<i && tmp[k]==tmp[j]; k ++);
			res = max(res, k-j);
		}
	}
	return res+1;
}
int main() {
	
	
	return 0;
}
