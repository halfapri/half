#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
typedef unsigned long long ull ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define pi (acos(-1.0))
#define fi first
#define se second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

bitset<220000>dp ;
int n ;
char s[20] ;
int D ;

int get (double x) {
	bool sign = x<0 ;
	if (sign) x=-x ;
	return (int) (x*10000+eps)*(sign?-1:1) ;
}

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	while (CASE --) {
		dp.reset() ;
	vector<int> pt ;
		dp[200000] = 1 ;
		double x ;
		scanf ("%lf%d" , &x , &n) ;
		D = get (x)+200000 ;
		for (int i=0 ; i<n ; i++) {
			scanf ("%lf" , &x) ;
			pt.push_back (get(x)) ;
		}
		sort (pt.begin(),pt.end()) ;
		for (int i:pt) {
			if (i<0) dp = dp | dp>>(-i) ;
			else dp = dp | dp<<i ;
		}
		int best = 200000 ;
		for (int i=0 ; i<220000 ; i++) {
			if (dp[i] && abs(best-D)>abs(i-D)) best = i ;
		}
		printf ("%.4f\n" , (best-200000)/10000.0) ;
	}
	return 0 ;
}
