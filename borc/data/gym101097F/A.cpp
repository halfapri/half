#include <stdio.h>
#include <time.h>
#include <bitset>
#include <string.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
#include <complex>
#include <functional>
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
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=91250681,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 300000+10;
int ls[M*60], rs[M*60], T[M*60], rt[M]; 
struct Persist {
#define mid (l+r>>1)
	const int upp = 1000000000+10;
	int sz;
	int init () {sz=0;return sz++;}
	inline int alloc (int o) {
		ls[sz]=ls[o], rs[sz]=rs[o], T[sz]=T[o];
		return sz++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int u,int l,int r,int pl,int pr,int lz) {
		if (pl<=l && r<=pr) {T[u]=min(T[u]+lz,upp); return;}
		if (pl<=mid) ins (ls[o],ls[u]=alloc(ls[o]),l,mid,pl,pr,lz);
		if (pr>mid) ins (rs[o],rs[u]=alloc(rs[o]),mid+1,r,pl,pr,lz);
	}
	ll ask (int o,int l,int r,int x) {
		ll ret = T[o];
		if (l == r) return ret;
		if (x<=mid) return ret+ask(ls[o],l,mid,x);
		else return ret+ask(rs[o],mid+1,r,x);
	}
#undef mid
}pst;

int n, m, k, p[M];
vector<int> g[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	freopen ("meteors.in", "r", stdin);
	freopen ("meteors.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i=0, x; i<m; i++) {
		scanf ("%d", &x);
		g[x].emplace_back (i+1);
	}
	for (int i=1; i<=n; i++) scanf ("%d", p+i);
	scanf ("%d", &k);
	pst.build (rt[0]=pst.init(),1,m);
	for (int i=1, l,r,a; i<=k; i++) {
		scanf ("%d%d%d", &l, &r, &a);
		int lst = rt[i-1];
		rt[i] = pst.alloc (lst);
		if (l<=r) pst.ins (lst,rt[i],1,m,l,r,a);
		else {
			pst.ins (lst,rt[i],1,m,1,r,a);
			lst = rt[i];
			rt[i] = pst.alloc (lst);
			pst.ins (lst,rt[i],1,m,l,m,a);
		}
	}
//////////////////////////////////////////////////////////////////
	auto judge = [&](int u,int x) {
		ll ret=0;
		for (int v:g[u]) ret += pst.ask(rt[x],1,m,v);
		return ret;
	};
////////////////////
	for (int i=1; i<=n; i++) {
		int l=1, r=k, ans=0;
		while (l<=r) {
			int mid = l+r>>1;
			if (judge(i,mid)>=p[i]) ans=mid,r=mid-1;
			else l=mid+1;
		}
		if (ans) printf ("%d\n", ans);
		else printf ("NIE\n");
	}
	return 0;
}
