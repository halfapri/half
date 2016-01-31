#include<bits/stdc++.h>
using namespace std;
#define pi (acos(-1.0)) 
typedef long long ll ;

const double eps = 1e-9 ;

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
bool cmp1 (const Point &a , const Point &b) {//polar angle sort(interger)
	return a.dim()==b.dim()?a*b>0 : a.dim()>b.dim() ;
}
bool cmp2 (const Point &a , const Point &b) {//ploar angle sort(double)
	return sign(atan2(a.y,a.x)-atan2(b.y,b.x)) < 0 ;
}
double dist (const Point &a , const Point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)) ;
}
double dist2 (const Point &a , const Point &b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) ;
}
double point_to_seg (const Point &a , const Point &b , const Point &dot) {
	if (dotji(dot-a,b-a)<0 || dotji(dot-b,a-b)<0) return min (dist(dot,a),dist(dot,b)) ;
	return fabs((a-dot)*(b-dot)) / dist(a,b) ;
}//dot到线段ab的最短距离

