//3D几何类库
using namespace std;
#define maxn 10010
# define M_PI		3.14159265358979323846	/* pi */
#define sqr(v) ((v)*(v))
const double eps = 1E-8;
int sig(double d) {
	return (d>eps) - (d<-eps);
}
struct Point {
	double x, y, z;
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	Point() {}
	Point operator + (const Point & p) const {
		return Point(x+p.x, y+p.y, z+p.z);
	}
	Point operator - (const Point & p) const {
		return Point(x-p.x, y-p.y, z-p.z);
	}
	Point operator * (const double & d) const {
		return Point(x*d, y*d, z*d);
	}
	Point resize(double d) {
		d /= sqrt(x*x+y*y+z*z);
		return Point(x*d, y*d, z*d);
	}
	double len() const {
		return sqrt(x*x+y*y+z*z);
	}
	bool operator < (const Point & p) const {
		return sig(x-p.x)!=0 ? x<p.x : sig(y-p.y)!=0 ? y<p.y : sig(z-p.z)<0;
	}
	bool operator == (const Point & p) const {
		return sig(x-p.x)==0 && sig(y-p.y)==0 && sig(z-p.z)==0;
	}
	void input() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void output() const {
		printf("x = %.2f, y = %.2f, z = %.2f\n", x, y, z);
	}
};
//点乘
double dot(const Point & a, const Point & b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
double dot(const Point & o, const Point & a, const Point & b) {
	return dot(a-o, b-o);
}
//叉乘
Point cross(const Point & a, const Point & b) {
	return Point(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}
Point cross(const Point & o, const Point & a, const Point & b) {
	return cross(a-o,b-o);
}
//两点距离
double dis(const Point & a, const Point & b) {
	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y) + sqr(a.z-b.z));
}
//点到直线距离
double dis(const Point & o, const Point & a, const Point & b) {
	return cross(o, a, b).len() / dis(a,b);
}
//返回o到ab直线的投影点, 对于o在ab上也适合
Point pointToLine(const Point & o, const Point & a, const Point & b) {
	Point fa = cross(o, a, b);	//oab的垂向量
	Point vec = cross(b-a, fa);	//vec为在oab平面上，且由o指向ab的一条向量
	return o + vec.resize(fa.len()/dis(a,b));
}
//判断三点共线
bool sameLine(const Point & a, const Point & b, const Point & c) {
	return sig(cross(a, b, c).len())==0;
}
//判断四点共面
bool sameFace(const Point & a, const Point & b, const Point & c, const Point & d) {
	return sig(dot(b-a, cross(a, c, d))) == 0;
}
//p绕着se向量，逆时针转ang角度
Point rotate(Point p, Point s, Point e, double ang) {
	if(sameLine(p, s, e)) {
		//sprintf("keke..\n");	error!
		return p;
	}
	Point fa1 = cross(s, e, p);
	Point fa2 = cross(e-s, fa1);
	
	double len = fabs(cross(p, e, s).len() / dis(e, s));	//圆心角
	fa2 = fa2.resize(len);
	fa1 = fa1.resize(len);
	Point h = p + fa2;
	Point pp = h + fa1;
	
	Point res = h + (p-h)*cos(ang) + (pp-h)*sin(ang);
	return res;
}
//vec是一个向量，将vec转到z轴向量，返回p点所转到的位置
Point rotate(Point p, Point vec) {
	Point z(0, 0, 1);
	Point fa = cross(vec, z);
	return rotate(p, Point(0,0,0), fa, acos( dot(z,vec)/vec.len() ));
}

struct Face {
	Point a, b, c;
	Face() {}
	Face(Point a, Point b, Point c) : a(a), b(b), c(c) {}
	Point fa() const {
		return cross(a, b, c);
	}
	bool same_side(Point q , Point  p){
		return sig ( dot(a - q, cross(q, b, c)) 
			* dot(a - p , cross(p, b, c)) ) > 0 ;
	}
	bool inFace(Point q) const {	//判断某点是否在该平面上
		return sameFace(a, b, c, q);
	}
	bool operator == (const Face & face) const {
		Point fa1 = fa();
		Point fa2 = face.fa();
		if(sig(cross(fa1,fa2).len())!=0)    return false;
		return inFace(face.a);
	}
};
//判断两直线平行
bool px(const Point & a, const Point & b, const Point & c, const Point & d) {
	return sig(cross(b-a, d-c).len()) == 0;
}
//判断直线与平面平行
bool px(const Face & f, const Point & a, const Point & b) {
	return sig(dot(f.fa(), b-a))==0;
}
//判断两平面平行
bool px(const Face & f1, const Face & f2) {
	return sig(cross(f1.fa(),f2.fa()).len()) == 0;
}
//判断两直线垂直
bool cz(const Point & a, const Point & b, const Point & c, const Point & d) {
	return sig(dot(b-a, d-a)) == 0;
}
//判断直线与平面垂直
bool cz(const Face & f, const Point & a, const Point & b) {
	return sig(cross(f.fa(), b-a).len()) == 0;
}
//判断两平面垂直
bool cz(const Face & f1, const Face & f2) {
	return sig(dot(f1.fa(), f2.fa())) == 0;
}
//点到平面距离
double dis(const Face & f, const Point & p) {
	Point fa = f.fa();
	return fabs(dot(fa, f.a-p) / fa.len());
}
//两直线距离
double dis(const Point & a, const Point & b, const Point & c, const Point & d) {
	Point fa = cross(b-a,d-c);
	if(fa.len() == 0) {	//两直线平行
		return cross(c, a, b).len() / dis(a, b);
		return dis(c, a, b);		//或者用这个，点到直线距离
	} else {
		return fabs(dot(c-a, fa) / fa.len());
	}
}

//求ab直线与f的交点，断言ab于f不平行
Point intersect(const Face & f, const Point & a, const Point & b) {
	Point fa = f.fa();
	double t = dot(fa,f.a-a) / dot(fa,b-a);
	return a+(b-a)*t;
}
//求两直线交点，【断言】两直线共面且不平行
Point intersect(const Point & a, const Point & b, const Point & c, const Point & d) {
	Point e = d + cross(a-b, c-d);
	return intersect(Face(c,d,e), a, b);
	//或者用下面代码：
	Point fa = cross(c, d, e);
	double t = dot(fa, c-a) / dot(fa, b-a);
	return a+(b-a) * t;
}
//求f1,f2的交线，断言f1与f2不平行
void intersect(const Face & f1, const Face & f2, Point & p1, Point & p2) {
	p1 = false==px(f2, f1.a, f1.b) ? intersect(f2, f1.a, f1.b) : intersect(f2, f1.b, f1.c);
	p2 = p1 + cross(f1.fa(), f2.fa());
}
//求两直线的共垂线, p1返回ab直线上的公垂线交点，p2返回cd直线上的公垂线交点
void gc(const Point & a, const Point & b, const Point & c, const Point & d, Point & p1, Point & p2) {
	Point e = d + cross(a-b, c-d);
	p1 = intersect(Face(c,d,e), a, b);
	p2 = pointToLine(p1, c, d);
}
//判断点是否在空间三角形内部, 包括边界, 【断言】abc不共线，并且oabc共面
bool inTriangle(const Point & o, const Point & a, const Point & b, const Point & c) {
	double s = cross(a, b, c).len();
	double s1 = cross(o, a, b).len();
	double s2 = cross(o, b, c).len();
	double s3 = cross(o, a, c).len();
//	return sig(s - s1 - s2 - s3) == 0;
	return sig(s-s1-s2-s3)==0 && sig(s1)==1 && sig(s2)==1 && sig(s3)==1;//不包括边界的版本
}
//判断某个点是否在线段上, 断言oab共线		-1表示在上面，0表示在线段边上，1表示在线段外
int onSeg(const Point & o, const Point & a, const Point & b) {
	return sig(dot(o, a, b));
}

/*
//ural1754	金字塔内一点的最近距离
double m, h, H;
Point p0, p1, p2, p3, p4;
int main() {
	while(cin >> m >> h >> H) {
		cin >> p0.x >> p0.y;	p0.z = h;
		cin >> p1.x >> p1.y;	p1.z = 0;
		cin >> p2.x >> p2.y;	p2.z = 0;
		cin >> p3.x >> p3.y;	p3.z = 0;
		cin >> p4.x >> p4.y;	p4.z = H;
		
		Face f1(p1, p2, p3);
		Face f2(p1, p2, p4);
		Face f3(p1, p3, p4);
		Face f4(p2, p3, p4);
		
		double ans = 1E30;
		ans = min(ans, dis(f1, p0));
		ans = min(ans, dis(f2, p0));
		ans = min(ans, dis(f3, p0));
		ans = min(ans, dis(f4, p0));
		
		if(sig(ans + h - m) <= 0) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
*/
/*
//poj-2852	两条直线公垂线的中点
int main() {
	double t;
	double ha, hb;
	
	double r = 10000.0;
	
	double a1, b1, a2, b2;
	cin >> t >> ha >> hb;
	
	Point A1(0, 0, ha), B1(100, 0, hb);
	
	for(int idx = 1; idx <= t; idx ++) {
		cin >> a2 >> b2 >> a1 >> b1;
		a1 = a1 * M_PI / 180;
		b1 = b1 * M_PI / 180;
		a2 = a2 * M_PI / 180;
		b2 = b2 * M_PI / 180;
		
		Point A2 = A1 + Point(cos(a1), sin(a1), tan(a2))*r;
		Point B2 = B1 + Point(cos(b1), sin(b1), tan(b2))*r;
		Point p, q;
		gc(A1, A2, B1, B2, p, q);
		
		printf("%d: %.0f\n", idx, (p.z+q.z)/2);
	}
	return 0;
}
*/
/*
//uva-11275	判断两个空间三角形是否有交点
//判断两个三角形是否有交点
bool intersect(Point * P1, Point * P2) {
	Face f1(P1[0], P1[1], P1[2]);
	Face f2(P2[0], P2[1], P2[2]);
	if(px(f1,f2)) {	//两三角形共面
		if(!sameFace(P1[0], P1[1], P1[2], P2[0]))	return false;
		for(int i = 0; i < 3; i ++) {
			if(inTriangle(P1[i], P2[0], P2[1], P2[2]) || 
					inTriangle(P2[i], P1[0], P1[1], P1[2]))
				return true;
		}
		return false;
	}
	Point l1, l2;
	intersect(f1, f2, l1, l2);	//公垂线
	
	Point arr1[3], arr2[3];
	int len1 = 0, len2 = 0, a, b;
	
	for(int i = 0; i < 3; i ++) {
		a = 0;	a+=a==i;
		b = a+1;b+=b==i;
		if(!px( P1[a], P1[b], l1,l2)) {
			arr1[len1] = intersect(P1[a], P1[b], l1, l2);
			if(onSeg(arr1[len1], P1[a], P1[b]) <= 0)	len1 ++;
		}
		if(!px( P2[a], P2[b], l1,l2)) {
			arr2[len2] = intersect(P2[a], P2[b], l1, l2);
			if(onSeg(arr2[len2], P2[a], P2[b]) <= 0)	len2 ++;
		}
	}
	sort(arr1, arr1+len1);
	sort(arr2, arr2+len2);
	len1 = unique(arr1, arr1+len1) - arr1;
	len2 = unique(arr2, arr2+len2) - arr2;
	if(len1 == 3 || len2 == 3)	while(1);	//assume not !
	if(len1 == 0 || len2 == 0)	return false;
	if(len1 == 1 && len2 == 1)	return arr1[0]==arr2[0];
	if(len1 == 2)
		for(int i = 0; i < len2; i ++)
			if(onSeg(arr2[i],arr1[0],arr1[1]) <= 0)return true;
	if(len2 == 2)
		for(int i = 0; i < len1; i ++)
			if(onSeg(arr1[i],arr2[0],arr2[1]) <= 0)return true;
	return false;
}
int main() {
	int t;
	Point p1[3], p2[3];
	for(scanf("%d", &t); t --; ) {
		for(int i = 0; i < 3; i ++)	p1[i].input();
		for(int i = 0; i < 3; i ++)	p2[i].input();
		printf("%d\n", intersect(p1, p2));
	}
	return 0;
}*/
/*
//福州网络赛fzu1981	求弓箭手射穿敌人的个数（所有弓箭手都沿着vec方向射箭）
Point ps1[maxn], ps2[maxn];
int n, m;
int main() {
	int t;
	scanf("%d", &t);
	for(int index=1; index<=t; index++) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i ++)	ps1[i].input();
		for(int i = 0; i < m; i ++)	ps2[i].input();
		Point vec;
		vec.input();
		
		for(int i = 0; i < n; i ++)	ps1[i] = rotate(ps1[i],vec);
		for(int i = 0; i < m; i ++)	ps2[i] = rotate(ps2[i],vec);
		
		sort(ps1, ps1+n);
		sort(ps2, ps2+m);
		
		int ans = 0;
		for(int i = 0; i < n; i ++) {
			int idx = upper_bound(ps2, ps2+m, ps1[i])-ps2-1;
			if(idx>=0 && idx<n) {
				if(sig(ps1[i].x-ps2[idx].x)==0 && sig(ps1[i].y-ps2[idx].y)==0) {
					ans ++;
				}
			}
		}
		printf("Case %d: %d\n", index, ans);
	}
	return 0;
}
*/


/*
//hdu-2693 3D camera
//O发出三条射线OA、OB、OC，判断三角形DEF是否有一点绝对在O-ABC包围的范围之内

double cross2d(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}
double dot2d(Point o, Point a, Point b) {
	return (a.x-o.x)*(b.x-o.x) + (a.y-o.y)*(b.y-o.y);
}
int lineCross(Point a, Point b, Point c, Point d, Point &p) {
	double s1, s2;
	s1=cross2d(a,b,c);
	s2=cross2d(a,b,d);
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
void polygon_cut(Point * p, int & n, Point a, Point b) {
	static Point pp[maxn];
	int m = 0;
	p[n] = p[0];
	for(int i = 0; i < n; i ++) {
		if(sig(cross2d(a, b, p[i])) > 0)
			pp[m ++] = p[i];
		if(sig(cross2d(a, b, p[i])) != sig(cross2d(a, b, p[i+1])))
			lineCross(a, b, p[i], p[i+1], pp[m ++]);
	}
	n = 0;
	for(int i = 0; i < m; i ++)
		if(!i || !(pp[i]==pp[i-1]))
			p[n ++] = pp[i];
	while(n>1 && p[n-1]==p[0])	n --;
}

Point poly[maxn];
int polyN;

bool deal(Face surf, Point o, Point a, Point b, Point c) {
	Face oab(o,a,b);
	bool ok = true;
	if( px(oab,surf) ) {
		if(sig(c.z-o.z)==0)	while(1);
		if(sig(o.z-surf.a.z)==0 || sig(c.z-o.z)>0) {
			ok = false;
		}
	} else {
		Point l1,l2;
		intersect(oab,surf,l1,l2);
		
		Point fa = cross(o,b,a);
		Point faL = l2-l1;
		
		faL = Point(-faL.y, faL.x, faL.z);
		
		if(sig(dot(faL,fa))<0)	swap(l1,l2);
		polygon_cut(poly, polyN, l1, l2);	//l1 l2的左侧!!!
	}
	return ok;
}

int main() {
	int t;
	for(scanf("%d", &t); t --; ) {
		Point o, a, b, c, d, e, f;
		
		o.input();
		a.input();	b.input();	c.input();
		d.input();	e.input();	f.input();
		
		Point vec = cross(d,e,f);
		if(sig(vec.len())==0)	while(1);
		
		o = rotate(o, vec);
		a=rotate(a,vec);	b=rotate(b,vec);	c=rotate(c,vec);
		d=rotate(d,vec);	e=rotate(e,vec);	f=rotate(f,vec);
		
		if(sig(o.z-d.z) < 0) {
			Point tmp(0,0,-1);
			o = rotate(o, tmp);
			a=rotate(a,tmp);	b=rotate(b,tmp);	c=rotate(c,tmp);
			d=rotate(d,tmp);	e=rotate(e,tmp);	f=rotate(f,tmp);
		}
		
		Face surf(d,e,f);		//水平面
		
		polyN = 3;
		poly[0] = d;
		poly[1] = e;
		poly[2] = f;
		
		Face oab(o,a,b);
		Face oac(o,a,c);
		Face obc(o,b,c);
		
		bool ok = true;
		
		ok &= deal(surf,o,a,b,c);
		ok &= deal(surf,o,b,c,a);
		ok &= deal(surf,o,c,a,b);
		if(ok) {
			if(sig(area(poly,polyN))==0) {
				ok = false;
			}
		}
		if(ok)	printf("YES\n");
		else	printf("NO\n");
	}
	return 0;
}
*/
//计算几何_三维凸包（面积＋面数）
int faces;		//凸包的面数
int sig(double x) {    return (x > 1E-6) - (x < -1E-6);		}
#define N 505
struct Point {
    double x, y, z;
    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point operator +(Point b) {
        return Point(x + b.x, y + b.y, z + b.z);
    }
    Point operator -(Point b) {
        return Point(x - b.x, y - b.y, z - b.z);
    }
    Point operator /(double t) {
        return Point(x / t, y / t, z / t);
    }
    double len() {
        return sqrt(x * x + y * y + z * z);
    }
};
double dot(Point a, Point b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Point cross(Point a, Point b) {
    return Point(a.y * b.z - a.z * b.y,
               -(a.x * b.z - a.z * b.x),
                 a.x * b.y - a.y * b.x);
}
Point ps[N];
struct Face {
    int a,b,c;
    Face(int a ,int b , int c ): a (a), b(b) , c(c) {}
    double area () {
        return cross( ps[b]-ps[a] , ps[c]-ps[a] ).len();
    }
    Point fa() const {
        return cross( ps[b]-ps[a] , ps[c]-ps[a] );
    }
    bool same_side(Point q , Point  p){
        return sig ( dot(ps[a] - q, cross(ps[b] - q, ps[c] - q)) 
            * dot(ps[a] - p , cross( ps[b] - p , ps[c] - p)) ) > 0 ;
    }
    bool inFace(Point q) const {	//判断某点是否在该平面上
        return sig(dot(ps[a] - q, cross(ps[b] - q, ps[c] - q)))==0;
    }
    bool operator == (const Face & face) const {
        Point fa1 = fa();
        Point fa2 = face.fa();
        if(sig(cross(fa1,fa2).len())!=0)    return false;
        return inFace(ps[face.a]);
    }
};
struct line {
    int a, b;
    line(int a, int b) : a(a),b(b){}
};
double convexHull(Point *ps, int n) {
#define judge(S, T)                                                \
map[C[j].S][C[j].T]=map[C[j].T][C[j].S]= map[C[j].S][C[j].T]==0;\
LT.push_back(line(C[j].S, C[j].T))
    static bool map[N][N];
    static vector <Face> C , FT;    //convex、face_tmp 
    static vector <line> LT;        //line_tmp 
    int i, j;
    if(n <= 2)    return 0.0;
    if(n == 3)    return cross(ps[1]-ps[0] , ps[2]-ps[0]).len()*0.5;
    C.clear();
    memset(map, 0 , sizeof(map));
    for(i = 0; i < 4; i ++)
        C.push_back(Face(i, (i+1)%4, (i+2)%4));
    Point center = (ps[0] + ps[1] + ps[2] + ps[3]) / 4;
    for(i = 4 ; i < n ; i ++ ) {
        FT.clear();
        LT.clear(); 
        for (j = 0 ; j < C.size() ; j ++ )
            if ( ! (C[j].same_side( center , ps[i] )) ) {
                judge(a, b);    judge(c, b);    judge(c, a);
            } else    FT.push_back(C[j]);
        C.clear();
        for(j = 0 ;j < FT.size() ; j ++ )
            C.push_back( FT[j] );
        for(j = 0 ;j < LT.size() ; j ++ )
            if (map [ LT[j].a ][ LT[j].b ]) {
                C.push_back( Face ( LT[j].a , LT[j].b , i ) );
                map[ LT[j].a ][ LT[j].b ] = map[ LT[j].b ][ LT[j].a ] = 0;
            }
    }
    double area = 0 ;
    for ( i = 0 ; i < C.size() ; i ++ )
        area += C[i].area();
    area /= 2.0;
    //以下代码用于统计面数
    faces = 0;
	for(int i = 0; i < C.size(); i ++) {
		bool ok = true;
		for(int j = i+1; j < C.size(); j ++) {
			if(C[i]==C[j]) {
				ok = false;
				break;
			}
		}
		faces += ok;
	}
    return area;
}
int main() {
    int n;
    double x, y, z;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i ++) {
            scanf("%lf%lf%lf", &x, &y, &z);
            ps[i] = Point(x, y, z);
        }
        while(sig(convexHull(ps, n)) == 0) {
            for(int j = n-1; j > 0; j --) {	//随机化，因为前四个必须不在一个平面上！
                swap(ps[j], ps[rand()%j]);
            }
        }
        printf("%d\n", faces);
    }
    return 0;
}

