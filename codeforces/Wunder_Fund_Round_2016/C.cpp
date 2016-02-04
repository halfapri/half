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
	ll x , y ;
	int id ;
	Point () {}
	Point(const ll &x , const ll &y ) : x(x) , y(y) {} 

	bool dim() const {return x < 0 || x == 0 && y < 0 ;}
} ;
Point operator + (const Point &a , const Point &b) {
	return Point(a.x + b.x , a.y + b.y) ;
}
Point operator - (const Point &a , const Point &b) {
	return Point(a.x - b.x , a.y - b.y) ;
}
ll operator * (const Point &a , const Point &b) {
	return a.x * b.y - a.y * b.x ;
}
ll dotji(const Point &a , const Point &b) {
	return a.x * b.x + a.y * b.y ;
}
bool cmp1 (const Point &a , const Point &b) {//polar angle sort
	return a.dim()==b.dim()?a*b>0 : a.dim()>b.dim() ;
}
bool cmp2 (const Point &a , const Point &b) {//polar angle sort
	return sign(atan2(a.y,a.x)-atan2(b.y,b.x)) < 0 ;
}
double dist (const Point &a , const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)) ;
}
ll dist2 (const Point &a , const Point &b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) ;
}
double modulus (const Point &a) {
	return sqrt(a.x*a.x+a.y*a.y) ;
}
ll modulus2 (const Point &a) {
	return a.x*a.x+a.y*a.y ;
}
int collinear (const Point &a , const Point &b) {
	return a*b?0:(dotji(a,b)>0?1:-1) ;
	//return !cmp1(a,b) && !cmp1(b,a) ;

}//0:不共线；1:同向共线；-1:反向共线


double point_to_seg (const Point &a , const Point &b , const Point &dot) {
	if (dotji(dot-a,b-a)<0 || dotji(dot-b,a-b)<0) return min (dist(dot,a),dist(dot,b)) ;
	return fabs((a-dot)*(b-dot)) / dist(a,b) ;
}//dot到线段ab的最短距离
int two_poles(Point a , Point b , int pole_a , int pole_b , int tot) {
	if (collinear(a,b)) return -1 ;
	return a*b>0?abs(pole_a-pole_b)-1:tot-abs(pole_a-pole_b)-1;
}//两个极之间形成的劣角间有几个极(为平角/0度角返回-1) , pole[M]

const int M = 1e5+10 ;
int n ;
Point a[M] , b[M] ;
int pole[M] ;

void make_min (int id) {
	ll minn = modulus2(b[id]) ;
	int minn_id = id ;
	for (int i = 0 ; i < n-1 ; i ++) {
		if (collinear(b[id],b[i])==1&&modulus2(b[i])<minn) {
			minn = modulus2(b[i]) ;
			minn_id = i ;
		}
	}
	printf ("%d " , b[minn_id].id+1) ;
}

int main () {
	scanf ("%d" , &n) ;
	for (int i = 0 ; i < n ; i ++) {
		scanf (LLD LLD , &a[i].x , &a[i].y) ;
	}
	for (int i = 0 ; i < n-1 ; i ++) {
		b[i] = Point (a[i].x-a[n-1].x,a[i].y-a[n-1].y ) ;
		b[i].id = i ;
	}
	sort (b , b+n-1 , cmp1) ;
	for (int i = 1 ; i < n-1 ; i ++) {
		if(collinear(b[i],b[i-1])==1) 
			pole[i]=pole[i-1];
		else pole[i]=pole[i-1]+1 ;
	} 
	//if (collinear(b[7],b[8])==1) puts ("YES") ;
	//for (int i = 0 ; i < n-1 ; i ++) {
	//	cout << "(" << b[i].x << "," << b[i].y << ")" << "," << "id=" << b[i].id << "," << "col=" << pole[i] <<endl ;
	//}
	printf ("%d " , n) ;
	for (int i = 0 ; i < n-1 ; i ++) {
		if (two_poles(b[i],b[(i+1)%(n-1)],pole[i],pole[(i+1)%(n-1)],pole[n-2]+1) == 0) {
		  make_min(i) ;	
		  make_min((i+1)%(n-1)) ;
		  break ;
		}
	}
	return puts ("") , 0 ;
}
