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

int sqr (int x) { return x*x ;}

struct Unit {
	int lz , rz , total , len ;
	Unit (int _lz=0,int _rz=0,int _total=0,int _len=0):
		lz(_lz),rz(_rz),total(_total),len(_len) {};
	
	Unit up (const Unit &rhs) const {
		Unit ret ;
		ret.lz = lz ;
		if (lz==len) ret.lz += rhs.lz ;
		ret.rz = rhs.rz ;
		if (rhs.rz==rhs.len) ret.rz += rz ;
		ret.total = total+rhs.total
			+rz*rhs.lz ;
		ret.len = len+rhs.len ;
		return ret ;
	}
} ;

const int M = 10000+10 ;
char Qs[M][2] ;
int Qx[M] , Qy[M] ; 
int a[M] ;
struct SegTree {
	Unit c[M<<2] ;

	void build (int o,int l,int r,int w) {
		if (l==r) {
			if (a[l]%w==0) 
				c[o] = Unit(1,1,1,1) ;
			else 
				c[o] = Unit(0,0,0,1) ;
			return ;
		}
		int mid=l+r>>1 ;
		build(lson,w) ; build(rson,w) ;
		c[o] = c[o<<1].up(c[o<<1|1]) ;
	}

	void update (int o,int l,int r,int pos,int x,int w) {
		if (l==r) {
			if (x%w==0)
				c[o] = Unit(1,1,1,1) ;
			else
				c[o] = Unit(0,0,0,1) ;
			return ;
		}
		int mid=l+r>>1 ;
		if (pos<=mid) update(lson,pos,x,w) ;
		else update(rson,pos,x,w) ;
		c[o]=c[o<<1].up(c[o<<1|1]) ;
	}

	Unit ask (int o,int l,int r,int pl,int pr) {
		if(pl<=l&&r<=pr)
			return c[o] ;
		int mid=l+r>>1 ;
		Unit ls , rs ;
		if (pl<=mid) ls=ask(lson,pl,pr) ;
		if (pr>mid) rs=ask(rson,pl,pr) ;
		return ls.up(rs) ;
	}
} seg ;
int g[M][101] ;
int n , Q ;

void solve () {
	for (int i=1 ; i<=100 ; i++) {
		seg.build(1,1,n,i) ;
		for (int j=0 ; j<Q ; j++) {
			if (Qs[j][0]=='M') 
				seg.update(1,1,n,Qx[j],Qy[j],i) ;
			else {
				g[j][i] = seg.ask(1,1,n,Qx[j],Qy[j]-1).total ;
				//printf ("g[%d][%d]=%d\n" , j,i,g[j][i]) ;
			}
		}
	}
	for (int i=0 ; i<Q ; i++) {
		if (Qs[i][0]=='M') continue ;
		int ans = 0 ;
		for (int j=100 ; j>0 ; j--) {
			for (int f=j+j ; f<=100 ; f+=j)
				g[i][j] -= g[i][f] ;
			if (g[i][j])
				ans ++ ;
		}
		printf ("%d\n" , ans) ;
	}
}

int main () {
	while (~ scanf("%d%d",&n,&Q)) {
		for (int i=1 ; i<=n ; i++) 
			scanf ("%d" , a+i) ;

		for (int i=0 ; i<Q ; i++) {
			scanf ("%s %d %d" , Qs[i],Qx+i,Qy+i) ;
			if (Qs[i][0]=='C')Qx[i]++ , Qy[i]++ ;
			else Qx[i]++ ;
		}

		solve () ;
	}
	return 0 ;
}
