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

int mp[1010][1010] ;
int a[2020] ;
int b[2020] ;
int n ;

int main () {
	scanf ("%d" , &n) ;
	for (int i = 0 ; i < n ; i ++) {
		int x , y ;
		scanf ("%d%d" , &x , &y) ;
		a[x+y] ++ ;
		if (y-x<0) b[y-x+2000]++ ;
		else b[y-x] ++ ;
	}
	ll tot = 0 ;
	for (int i = 0 ; i < 2020 ; i ++) {
		tot += 1ll*a[i]*(a[i]-1)/2 ;
		tot += 1ll*b[i]*(b[i]-1)/2 ;
	}
	printf (LLD "\n" , tot) ;
	return 0 ;
}
