#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
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
#define sqr(x) ((x)*(x))
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

const int M = 2000+10 ;
int n , m , a[M] , b[M] ;
int dp[M] , dptmp[M] ;

void solve () {
	fill(dp,dp+n+1,inf) ;
	fill(dptmp,dptmp+n+1,inf) ;
	int last = -1 , cnt = 0 ;
	for (int i=1 ; i<=n ; i++) {
		if (b[1] == a[i]) {
			dp[i] = cnt ++ ;
			if (last==-1) last = i ;
		}
	}
	dp[n+1] = cnt ;
	for (int i=2 ; i<=m ; i++) {
		//printf ("%d:min=%d\n" , i-1 , dp[n+1]) ;
		int minn = 0 ;
		int lasttmp = last , cur = 0 , ans = 0 ;
		last = n+1 , cnt = 0 ;
		for (int j=lasttmp+1; j<=n ; j++) {
			if (b[i] == a[j]) { 
				dptmp[j] = min (dptmp[j] , minn + cnt++) ;
				if (last==n+1) last = j ;
			}
			minn = min (minn , dp[j]-cnt) ;
		}
		dp[n+1] = min (dp[n+1] , minn+cnt) ;
		for (int j=1 ; j<=n ; j++) dp[j] = dptmp[j] ;
		fill (dptmp,dptmp+1+n,inf) ;
	}
	printf ("%d\n" , dp[n+1]) ;
}

int main () { 
	while (~ scanf ("%d%d",&n,&m)) {
		for (int i=1 ; i<=n ; i++) scanf ("%d" , a+i) ;
		for (int i=1 ; i<=m ; i++) scanf ("%d" , b+i) ;
		solve () ;
	}
	return 0 ;
}
