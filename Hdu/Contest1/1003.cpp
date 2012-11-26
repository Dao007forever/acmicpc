#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

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
	freopen("1003", "r", stdin);
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
