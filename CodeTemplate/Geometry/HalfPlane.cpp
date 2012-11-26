#define maxn 55
double my_sqrt(double d) {return sqrt(max(d, 0.0));}
double my_acos(double d) {return acos(d<-1?-1:d>1?1:d);}
#define sqr(v) ((v)*(v))
const double eps = 1E-8;
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
	double operator * (const Point &b) const {
		return x * b.y - y * b.x;
	}
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
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	void output() {
		printf("x = %.2f, y = %.2f\n", x, y);
	}
}ps[maxn];
struct hplane {
	Point s,t;
	double ang;
	Point cross (const hplane &b) const {
		double s1 = (b.t-s) * (b.s-s);
		double s2 = (b.s-t) * (b.t-t);
		return Point((s.x*s2+t.x*s1) / (s2+s1), (s.y*s2+t.y*s1) / (s2+s1));
	}
	bool operator < (const hplane &b) const {
		if (sig(b.ang - ang) != 0)
			return ang < b.ang;
		return sig((b.t-b.s)*(t-b.s)) >= 0;
	}
};
hplane Planes[100010],Q[100010];
Point Anss[100010];

void add_hplane(Point s,Point t,int &cnt) {
	Planes[cnt].s = s;
	Planes[cnt].t = t;
	Planes[cnt].ang = atan2(t.y-s.y,t.x-s.x);
	cnt++;
}

bool isright(hplane h, Point p) {
	double num = (p-h.s) * (h.t-h.s);
	return sig(num)>0;
}

int hpi(int cnt) {
	//step1. 将所有半平面按极角排序，对于极角相同的，选择性的保留一个
	sort(Planes, Planes + cnt);
	int len = 1 ;
	for (int i = 1; i < cnt; i++)
		if (sig(Planes[i].ang - Planes[i-1].ang) != 0)
			Planes[len++] = Planes[i];
	//step2. 使用一个双端队列(deque)，加入最开始2个半平面
	cnt = len;
	Q[0] = Planes[0];
	Q[1] = Planes[1];
	//step3. 每次考虑一个新的半平面：
	//	  a.while deque顶端的两个半平面的交点在当前半平面外:删除deque顶端的半平面
	//	  b.while deque底部的两个半平面的交点在当前半平面外:删除deque底部的半平面
	//	  c.将新半平面加入deque顶端
	int l = 0, r = 1;
	for (int i = 2; i < cnt; i++) {
		while (l < r && isright(Planes[i], Q[r].cross(Q[r-1]))) r--;
		while (l < r && isright(Planes[i], Q[l].cross(Q[l+1]))) l++;
		Q[++r] = Planes[i];
	}
	//step4.删除两端多余的半平面。
	//	具体方法是：
	//	a.while deque顶端的两个半平面的交点在底部半平面外:删除deque顶端的半平面
	//	b.while deque底部的两个半平面的交点在顶端半平面外:删除deque底部的半平面
	//	重复a,b直到不能删除为止。
	while (l < r && isright(Q[l], Q[r].cross(Q[r-1]))) r--;
	while (l < r && isright(Q[r], Q[l].cross(Q[l+1]))) l++;
	//step5.计算出deque顶端和底部的交点即可。
	if (r <= l + 1) return 0;
	len = 0;
	for (int i = l; i < r; i++)
		Anss[len++] = Q[i].cross(Q[i+1]);
	Anss[len++] = Q[l].cross(Q[r]);
	//step6. 去除共线的点
	int tcnt = 1;
	for (int i = 1; i < len; i++)
		if (!(Anss[i] == Anss[i-1])) Anss[tcnt++] = Anss[i];
	if (tcnt != 1 && Anss[tcnt-1] == Anss[0]) tcnt--;
	return tcnt;
}
