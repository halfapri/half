#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
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

int sign (ld x) { return x < -eps ? -1 : x > eps ; }

bool bigger (const complex<ld> &a , const complex<ld> &b) {
	if (sign(imag(a)) == 0 && sign(imag(b)) == 0) 
		return sign (real(a)-real(b)) > 0 ;
	if (sign(imag(a)) == 1 && sign(imag(b)) == 1) 
		return sign (real(a)-real(b)) < 0 ;
	return sign(imag(a)-imag(b)) < 0 ;
}//a>b , return 1 ; 

complex<ld> x , y , z , maxn ; 
string s = "x^y^z" ;

int main () {
	cin >> x >> y >> z ;
	maxn = z*log(y) + log(log(x)) ;

	if (bigger(y*log(z) + log(log(x)) , maxn)) {
		maxn = y*log(z) + log(log(x)) ;
		s = "x^z^y" ;
	}
	if (bigger(log(y*z) + log(log(x)) , maxn) ) {
		maxn = log(y*z) + log(log(x)) ;
		s = "(x^y)^z" ;
	}
	if (bigger(z*log(x) + log(log(y)) , maxn) ) {
		maxn  = z*log(x) + log(log(y)) ;
		s = "y^x^z" ;
	}
	if (bigger(x*log(z) + log(log(y)) , maxn) ) {
		maxn  = x*log(z) + log(log(y)) ;
		s = "y^z^x" ;
	}
	if (bigger(log(x*z) + log(log(y)) , maxn) ) {
		maxn = log(x*z) + log(log(y)) ;
		s = "(y^x)^z" ;
	}
	if (bigger(y*log(x) + log(log(z)) , maxn) ) {
		maxn  = y*log(x) + log(log(z)) ;
		s = "z^x^y" ;
	}
	if (bigger(x*log(y) + log(log(z)), maxn) ) {
		maxn = x*log(y) + log(log(z)) ;
		s = "z^y^x" ;
	}
	if (bigger(log(x*y) + log(log(z)), maxn) ) {
		maxn = log(x*y) + log(log(z)) ;
		s = "(z^x)^y" ;
	}
	cout << s << endl ;
	return 0 ;
}
