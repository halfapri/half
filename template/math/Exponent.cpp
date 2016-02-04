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
}//a>b , return 1 ;用于处理x^y^z这种问题，因为log(log(x^y^z))可能会变成复数
