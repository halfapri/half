#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)1e18 ;

const int M = 2e5+10 ;
int n , k ;
int a[M] ;

int get_left (int l , int r , int cnt) {
	int tmp = -cnt/2 ;
	tmp = max (l+1 , tmp) ;
	tmp = min (r-cnt , tmp) ;
	return tmp ;
}

void solve () {
	int l , r ;
	int cnt = 0 ;
	for (int i = 0 ; i < n && i < k; i ++) {
		l = -inf ;
		for (int j = i ; j < n+k ; j += k) {
			if (a[j] == inf) {
				cnt ++ ;
				continue ;
			}
			r = j<n ? a[j] : inf ;
			if (l+cnt >= r) {
				puts ("Incorrect sequence") ;
				exit(0) ;
			}
			int tmp = get_left(l , r , cnt) ;
			for (int f = j-cnt*k ; f < j ; f += k) {
			   a[f] = tmp ++ ;
			}
			l = r ;
			cnt = 0 ;
		}
	}
	for (int i = 0 ; i < n ; i ++) printf ("%d " , a[i]) ; puts ("") ;
}

int main () {
	cin>>n>>k ;
	for (int i = 0 ; i < n ; i ++) {
		if (scanf ("%d" , &a[i]) < 1) {
			scanf (" ?") ;
			a[i] = inf ;
		}
	}
	solve () ;
	return 0 ;
}
