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
#define sqr(x) ((x)*(x))
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

const int M = 50000+10 ;
struct STAFF {
	int id,loy,abi ;
	inline bool operator < (const STAFF &rhs) const {
		if (abi==rhs.abi) return id<rhs.id ; 
		return abi > rhs.abi ;
	}
} a[M] ;

struct NODE {
	int id,loy ;
	NODE (int _id=0,int _loy=0):id(_id),loy(_loy){}
	inline NODE up (const NODE &rhs) {
		NODE ret = NODE(-1,max(loy,rhs.loy)) ;
		if (ret.loy==loy) ret.id = id ;
		else ret.id = rhs.id ;
		return ret ;
	}
} ;
struct SEGTREE {
	NODE T[M<<3] ;
	void build (int o,int l,int r) {
		T[o] = NODE (-1,-inf) ;
		if (l==r) return ;
		int mid = l+r>>1 ;
		build (lson) ; build (rson) ;
	}
	NODE ask (int o,int l, int r,int pl,int pr) {
		if (pl<=l&&r<=pr) return T[o] ;
		int mid = l+r>>1 ;
		NODE ls(-1,-inf) , rs(-1,-inf) ;
		if (pl<=mid) ls = ask(lson,pl,pr) ; 
		if (pr>mid) rs = ask(rson,pl,pr) ;
		return ls.up(rs) ;
	}
	void update (int o,int l,int r,int x,NODE f) {
		if (l==r) { T[o] = T[o].up(f) ; return ; }
		int mid = l+r>>1 ;
		if (x<=mid) update(lson,x,f) ;
		else update(rson,x,f) ;
		T[o] = T[o<<1].up(T[o<<1|1]) ;
	}
} sgt ;

int tin[M<<1],tout[M<<1] , tim ;
vector<int> g[M] ;
void dfs (int u) {
	tin[u] = ++tim ;
	for (int v:g[u]) dfs (v) ;
	tout[u] = ++tim ;
}
int ans[M],n,m;

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	while (CASE --) {
		scanf ("%d%d" ,&n,&m) ;
		tim = 0 ;
		for (int i=0 ; i<n ; i++) g[i].clear () ;
		for (int v=1,u ; v<n ; v++) {
			scanf ("%d%d%d" , &u,&a[v].loy,&a[v].abi) ;
			a[v].id = v ;
			g[u].push_back(v) ;
		}
		dfs (0) ;
		sort (a+1 , a+n) ;
		sgt.build (1,1,n<<1) ;
		for (int i=1 ; i<n ; i++) { int x = a[i].id ;
			ans[x]=sgt.ask(1,1,n<<1,tin[x],tout[x]).id ;
			sgt.update (1,1,n<<1,tin[x],NODE(x,a[i].loy)) ;
			sgt.update (1,1,n<<1,tout[x],NODE(x,a[i].loy)) ;
		}
		while (m --) { int x ; scanf ("%d" , &x) ;
			printf ("%d\n" , ans[x]) ;
		}
	}
	return 0 ;
}
