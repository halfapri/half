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

int n ;
int a[100100] ;
int main () {
	scanf ("%d" , &n) ;
	for (int i = 0 ; i < n ; i ++) scanf ("%d" , &a[i]) ;
	sort (a,a+n) ;
	ll tot = 0 ;
	ll lst = 0 ;
	for (int i = n-1 ; i >= 0 ; i --) {
		if (!(a[i]&1)) {
			tot += 1ll*a[i] ;
		}
		else {
			lst += 1ll*a[i] ;
			if (!(lst&1)) {
				tot += lst ;
				lst = 0 ;
			}
		}
	}
	printf (LLD , tot) ;
	return 0 ;
}

