#include <stdio.h>
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
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 100000+10;
struct NODE {
	int len, maxn, xl, rx;
	NODE *ls, *rs;
	NODE () {len=maxn=xl=rx=0;}
	NODE merge (const NODE &rhs) {
		NODE ret;
		ret.len = len+rhs.len;
		ret.xl = xl;
		ret.rx = rhs.rx;
		if (xl == len) ret.xl += rhs.xl;
		if (rhs.rx == rhs.len) ret.rx += rx;
		ret.maxn = max (maxn, rhs.maxn);
		ret.maxn = max (ret.maxn, max(ret.xl, ret.rx));
		ret.maxn = max (ret.maxn, rx+rhs.xl);
		return ret;
	}
}T[M*22], *rt[M];

struct PERSIST {
	int sz;
	NODE *init () {sz=0; return alloc(T);}
	inline NODE *alloc (NODE *x) {T[sz]=*x; return T+sz++;}
	void build (NODE *o,int l,int r) {
		o->len = r-l+1;
		o->maxn = o->xl = o->rx = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (o->ls=alloc(T),l,mid);
		build (o->rs=alloc(T),mid+1,r);
	}
	inline void up (NODE *u) {
		u->rx = u->rs->rx, u->xl = u->ls->xl;
		if (u->rs->rx == u->rs->len) u->rx +=u->ls->rx;
		if (u->ls->xl == u->ls->len) u->xl += u->rs->xl;
		u->maxn = max (u->ls->maxn, u->rs->maxn);
		u->maxn = max (u->rx, max (u->xl, u->maxn));
		u->maxn = max (u->maxn, u->ls->rx + u->rs->xl);
	}
	void ins (NODE *o,int l,int r,NODE *u,int x) {
		if (l == r) { u->maxn = u->xl = u->rx = 1; return; }
		int mid = l+r>>1;
		if (x<=mid) ins (o->ls,l,mid,u->ls=alloc(o->ls),x);
		else ins (o->rs,mid+1,r,u->rs=alloc(o->rs),x);
		up (u);
	}
	NODE ask (NODE *o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return *o;
		int mid = l+r>>1;
		NODE lhs, rhs;
		if (pl<=mid) lhs = ask (o->ls,l,mid,pl,pr);
		if (pr>mid) rhs = ask (o->rs,mid+1,r,pl,pr);
		return lhs.merge (rhs);
	}
}sgt;

int n, m;
pair<int,int> h[M];
int ss[M], sz;

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	sz = 0;
	for (int i=1; i<=n; i++) {
		scanf ("%d", &h[i].fi);
		h[i].se = i;
		ss[sz++] = h[i].fi;
	}
	sort (h+1, h+n+1, [&](pair<int,int>a, pair<int,int>b) {
			return a.fi>b.fi;
			});
	sort (ss, ss+sz);
	sz = unique (ss, ss+sz) - ss;
	sgt.build (rt[sz]=sgt.alloc(T),1,n);
	for (int t=sz-1, i=1; t>=0; t--) {
		rt[t] = rt[t+1];
		while (i<=n && h[i].fi == ss[t]) {
			NODE *lst = rt[t];
			sgt.ins (lst,1,n,rt[t]=sgt.alloc(lst),h[i].se);
			i ++;
		}
	}
//////////////////////////////////////////////////////////////////
	auto bins = [&](int pl,int pr,int len) {
		int l=0, r=sz-1, ret=0;
		while (l<=r) {
			int mid = l+r>>1;
			int maxn = sgt.ask(rt[mid],1,n,pl,pr).maxn;
			if (maxn>=len) ret=mid,l=mid+1;
			else r=mid-1;
		}
		return ss[ret];
	};
//////////////////////////////
	scanf ("%d", &m);
	while (m --) {int pl, pr, len;
		scanf ("%d%d%d", &pl, &pr, &len);
		printf ("%d\n", bins(pl,pr,len));
	}
	return 0;
}
