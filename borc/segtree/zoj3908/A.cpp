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
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;

const int M = (int)1e5+10 ;
const int upp = (int)1e7+10 ;
bool prime[upp] ;
void get_prime () {
	prime[1] = 1 ;
	for (int i=2 ; i<upp ; i++) { if (!prime[i]) 
		for (int j=i+i ; j<upp ; j+=i) 
			prime[j] = 1 ;
	}
}

int a[M] ;
struct segtree {
	int c[M<<2] , a[M] , mark[M<<2] ;

	void up (int o) {
		c[o] = c[o<<1]+c[o<<1|1] ;
	}

	void down (int o,int l,int r) {
		if (mark[o]!=-1) {
			mark[o<<1]=mark[o<<1|1]=mark[o] ;
			int mid=l+r>>1 ;
			c[o<<1]=(mid-l+1)*(!prime[mark[o]]) ;
			c[o<<1|1]=(r-mid)*(!prime[mark[o]]) ;
			if (mid==l) a[l]=mark[o] ;
			if (mid+1==r) a[r]=mark[o] ;
			mark[o] = -1 ;
		}
	}

	void build (int o , int l , int r) {
		if (l==r) {
			scanf ("%d" , a+l) ;
			c[o] = !prime[a[l]] ;
			mark[o] = -1 ;
			return ;
		}
		int mid=l+r>>1 ;
		build (lson) ; build (rson) ;
		mark[o] = -1 ;
		up(o) ;
	}

	void update (int o,int l,int r,int pl,int pr,bool flag,int x) {
		if (pl<=l&&r<=pr) {
			if (flag) {
				a[l]+=x ;
				c[o] = !prime[a[l]] ;
			} else {
				mark[o] = x ;
				c[o] = (r-l+1)*(!prime[x]) ;
				if (l==r) a[l] = x ;
			} return ;
		}
		down (o,l,r) ;
		int mid = l+r>>1 ;
		if (pl<=mid) update(lson,pl,pr,flag,x) ;
		if (pr>mid) update(rson,pl,pr,flag,x) ;
		up (o) ;
	}

	int ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l&&r<=pr) 
			return c[o] ;
		down(o,l,r) ;
		int mid=l+r>>1 ,ls=0 ,rs=0;
		if (pl<=mid) ls = ask(lson,pl,pr) ;
		if (pr>mid) rs = ask(rson,pl,pr) ;
		up(o) ;
		return ls+rs ;
	}
} seg ;
int n , Q ;

int main () {
	get_prime() ;
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d%d" , &n ,&Q) ;
		seg.build(1,1,n) ;
		while (Q --) {
			char s[2] ;
			scanf ("%s" , s) ;
			if (s[0]=='A') {
				int v , l ;
				scanf ("%d%d" , &v , &l) ;
				seg.update(1,1,n,l,l,1,v) ;
			} else if (s[0]=='R') {
				int a , l , r ;
				scanf ("%d%d%d",&a,&l,&r) ;
				seg.update(1,1,n,l,r,0,a) ;
			} else if (s[0]=='Q') {
				int l , r ;
				scanf ("%d%d" , &l , &r) ;
				printf ("%d\n" , seg.ask(1,1,n,l,r)) ;
			}
		}
	}
	return 0 ;
}
