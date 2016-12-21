#pragma comment(linker, "/STACK:1024000000,1024000000")
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

const int M = 100000+10 ;
int orm[M<<1];
ll dis[M] ; 
struct NODE {
	ll val , add;
	inline void mark (ll x) {
		val += x ;
		add += x ;
	}
} ;
struct SEGTREE {
	NODE T[M<<3] ;
	void up (int o) {
		T[o].val = max (T[o<<1].val , T[o<<1|1].val) ;
	}
	void down (int o) {
		if (T[o].add==0) return ;
		T[o<<1].mark(T[o].add) ;
		T[o<<1|1].mark(T[o].add) ;
		T[o].add = 0 ;
	}
	void build (int o,int l,int r) {
		T[o].add = 0 ;
		if (l==r) {
			T[o].val = dis[orm[l]] ;
			return ;
		}
		int mid = l+r>>1 ;
		build(lson) ; build (rson) ;
		up (o) ;
	}
	ll ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l&&r<=pr) return T[o].val ;
		down(o) ;
		int mid = l+r>>1 ;
		ll ls=-INF ,rs=-INF ;
		if (pl<=mid) ls = ask(lson,pl,pr) ;
		if (pr>mid) rs = ask(rson,pl,pr) ;
		up(o) ;
		return max(ls,rs) ;
	}
	void update (int o,int l,int r,int pl,int pr,ll val) { 
		if (pl<=l&&r<=pr) { T[o].mark(val) ; return ; }
		down (o) ;
		int mid = l+r>>1 ;
		if (pl<=mid) update (lson,pl,pr,val) ;
		if (pr>mid) update (rson,pl,pr,val) ;
		up (o) ;
	}
}sgt ;
int tin[M] , tout[M] , tim , n , m , val[M] ;
struct EDGE {
	int v,nxt ;
} edge[M<<1];
int head[M] , E ;
void dfs (int o,int u) {
	dis[u] = dis[o] + val[u] ;
	tin[u] = ++tim ; orm[tim] = u ;
	for (int i=head[u] ; ~i ; i=edge[i].nxt) {
		int v = edge[i].v ;
		if (v!=o) dfs (u,v) ;
	}
	tout[u] = ++tim ; orm[tim] = u ;
}

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	dis[0] = 0 ;
	for (int cas=1 ; cas<=CASE ; cas ++) {
		scanf ("%d%d" , &n,&m) ;
		E = tim = 0 ;
		memset (head , -1 , sizeof(int)*(n+10)) ;
		for (int i=0,u,v; i<n-1 ; i++) {
			scanf ("%d%d" , &u,&v) ;
			u ++ , v ++ ;
			edge[E] = EDGE{v,head[u]} ;
			head[u] = E ++ ;
			edge[E] = EDGE{u,head[v]} ;
			head[v] = E ++ ;
		}
		for (int i=1 ; i<=n ; i++) scanf ("%d" , val+i) ; 
		dfs (0 , 1) ;
		sgt.build(1,1,n<<1) ;
		printf ("Case #%d:\n" , cas) ;
		while (m --) { int type,x,y ;
			scanf ("%d" , &type) ;
			if (type) {
				scanf ("%d" , &x) ; x ++ ;
				printf (LLD "\n" , sgt.ask(1,1,n<<1,tin[x],tout[x])) ;
			}
			else { 
				scanf ("%d%d" , &x,&y) ; x ++ ;
				sgt.update (1,1,n<<1,tin[x],tout[x],y-val[x]) ;
				val[x] = y ;
			}
		}
	}
	return 0 ;
}
