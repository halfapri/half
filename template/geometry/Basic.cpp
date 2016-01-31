#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define pi (acos(-1.0))
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)1e18 ;

int sign(double x) {return x < -eps ? -1 : x > eps ;}
struct Point {
	double x , y ;
	Point(const double &x , const double &y) : x(x) , y(y) {} 

	bool dim() const {return x < 0 || x == 0 && y < 0 ;}
} ;
Point operator + (const Point &a , const Point &b) {
	return Point(a.x + b.x , a.y + b.y) ;
}
Point operator - (const Point &a , const Point &b) {
	return Point(a.x - b.x , a.y - b.y) ;
}
double operator * (const Point &a , const Point &b) {
	return a.x * b.y - a.y * b.x ;
}
double dotji(const Point &a , const Point &b) {
	return a.x * b.x + a.y * b.y ;
}
bool cmp1 (const Point &a , const Point &b) {//polar angle sort
	return a.dim()==b.dim()?a*b>0 : a.dim()>b.dim() ;
}
bool cmp2 (const Point &a , const Point &b) {//ploar angle sort
	return sign(atan2(a.y,a.x)-atan2(b.y,b.x)) < 0 ;
}
double dist (const Point &a , const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)) ;
}
double dist2 (const Point &a , const Point &b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) ;
}
int collinear (const Point &a , const Point &b) {
	return a*b?0:dotji(a,b)>0 ;
}//0:不共线；1:同向共线；-1:反向共线


double point_to_seg (const Point &a , const Point &b , const Point &dot) {
	if (dotji(dot-a,b-a)<0 || dotji(dot-b,a-b)<0) return min (dist(dot,a),dist(dot,b)) ;
	return fabs((a-dot)*(b-dot)) / dist(a,b) ;
}//dot到线段ab的最短距离

