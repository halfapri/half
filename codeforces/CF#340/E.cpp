#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
const int M = 1e5+10;
int n , m , k ;
int a[M] ;
ll res[M] ;
int cnt[1<<20] ;

struct query {
	int l , r , id ;
} q[M] ;
int bk ;

bool cmp (query a , query b) {
	if (a.l/bk == b.l/bk) return a.r<b.r ;
	return a.l/bk < b.l/bk ;
}

void solve () {
	ll tot = 0 ;
	int l = 1 , r = 0 ;
	cnt[0] = 1 ;
	for (int i = 0 ; i < m ; i ++) {
		while (r < q[i].r) {
			r ++ ;
			tot += cnt[a[r]^k] ;
			cnt[a[r]] ++ ;
		}
		while (r > q[i].r) {
			cnt[a[r]] -- ;
			tot -= cnt[a[r]^k] ;
			r -- ;
		}
		while (l < q[i].l) {
			cnt[a[l-1]] -- ;
			tot -= cnt[a[l-1]^k] ;
			l ++ ;
		}
		while (l > q[i].l) {
			l -- ;
			tot += cnt[a[l-1]^k] ;
			cnt[a[l-1]] ++ ;
		}
		res[q[i].id] = tot ;
	}
	for (int i = 0 ; i < m ; i ++) printf ("%I64d\n" , res[i]) ;
}

int main () {
	cin>>n>>m>>k ;
	bk = sqrt(1.0*n) ;
	for (int i = 1 ; i <= n ; i ++) {
		scanf ("%d" , &a[i]) ;
	}
	for (int i = 0 ; i < m ; i ++) {
		scanf ("%d%d" , &q[i].l,&q[i].r) ;
		q[i].id = i ;
	}
	sort (q,q+m,cmp) ;
	for (int i = 1 ; i <= n ; i ++) a[i] ^= a[i-1] ;
	solve () ;
	return 0 ;
}
