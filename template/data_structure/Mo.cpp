#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
const int M = 1e5+10 ;
int n , m ;
int a[M] ;
ll res[M] ;
int bk ;
struct Mo {
	int l , r , id ;
}mo[M] ;

bool cmp (Mo a , Mo b) {
	if (a.l/bk == b.l/bk) return a.r<b.r ;
	return a.l/bk < b.l<bk ;
}

void solve () {
	int l = 1 , r = 0 ;
	ll tot = 0 ;
	for (int i=0 ; i<m ; i++) {
		while (r<mo[i].r) {
			r ++ ;
			//
		}
		while (r>mo[i].r) {
			//
			r -- ;
		}
		while (l<mo[i].l) {
			//
			l ++ ;
		}
		while (l>mo[i].l) {
			l -- ;
			//
		}
		res[mo[i].id] = tot ;
	}
	for (int i=0 ; i<m ; i++) printf ("%I64d\n" , res[i]) ;
}

int main () {
	cin>>n>>m ;
	bk = sqrt(1.0*n) ;
	for (int i=1;i<=n;i++) scanf ("%d" , &a[i]) ;
	
	sort (mo,mo+m,cmp) ;
	solve () ;
	return 0 ;
}
