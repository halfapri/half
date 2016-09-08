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

const int M = 20000+10;
int ls[M*22], rs[M*22], rt[M];

struct NODE {
	int xl, rx, sum;
	NODE () {xl=rx=sum=0;}
	inline NODE merge (NODE &rhs) {
		NODE f;
		f.xl = max (xl, sum+rhs.xl); 
		f.rx = max (rhs.rx, rhs.sum+rx);
		f.sum = sum + rhs.sum;
		return f;
	}
} T[M*22];

struct PERSIST {
	int sz;
	int init () {sz=0;return sz ++;}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz ++;
	}
	void build (int o,int l,int r) {
		T[o].xl = T[o].rx = T[o].sum = r-l+1;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x) {
		if (l == r) {T[u].xl = T[u].rx = T[u].sum = -1;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]].merge (T[rs[u]]);
	}
	NODE ask (int o,int l,int r,int pl,int pr) {
		if (pl>pr) return NODE ();
		if (pl<=l && r<=pr) return T[o];
		int mid = l+r>>1;
		NODE lhs, rhs;
		if (pl<=mid) lhs = ask (ls[o],l,mid,pl,pr);
		if (pr>mid) rhs = ask (rs[o],mid+1,r,pl,pr);
		if (pl<=mid && pr>mid) return lhs.merge (rhs);
		if (pl<=mid) return lhs;
		if (pr>mid) return rhs;
	}
} sgt;

typedef pair<int,int> pii;
int n, m, ss[M], sz; 
pii a[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	sz = 0;
	ss[sz ++] = -inf;
	for (int i=0; i<n; i++) {
		scanf ("%d", &a[i].fi);
		a[i].se = i;
		ss[sz ++] = a[i].fi;
	}
	sort (a, a+n);
	sort (ss, ss+sz);
	sz = unique (ss, ss+sz) - ss;
	sgt.build (rt[0]=sgt.init(),0,n-1);
	for (int t=1, i=0; t<sz; t++) {
		rt[t] = rt[t-1];
		while (i<n && ss[t] == a[i].fi) {
			int lst = rt[t];
			sgt.ins (lst,0,n-1,rt[t]=sgt.alloc(lst),a[i].se);
			i ++;
		}
	}
//////////////////////////////////////////////////////////////////
	scanf ("%d", &m);
	int x = 0, q[4];
	while (m --) {
		for (int i=0; i<4; i++) {
			scanf ("%d", q+i);
			q[i] = (q[i]+x)%n;
		}
		sort (q,q+4);
		//for (int i=0; i<4; i++) printf ("%d ", q[i]); puts ("");
		int l=1, r=sz-1, ret=0;
		while (l<=r) {
			int mid = l+r>>1;
			int sum = sgt.ask(rt[mid],0,n-1,q[1]+1,q[2]-1).sum+
				sgt.ask(rt[mid],0,n-1,q[0],q[1]).rx +
				sgt.ask(rt[mid],0,n-1,q[2],q[3]).xl;
			//printf ("ss=%d\n", ss[mid]);
			//printf ("%d %d %d\n",
			//sgt.ask(rt[mid],0,n-1,q[1]+1,q[2]-1).sum,
			//	sgt.ask(rt[mid],0,n-1,q[0],q[1]).rx ,
			//	sgt.ask(rt[mid],0,n-1,q[2],q[3]).xl);
			if (sum>=0) ret = mid, l = mid+1;
			else r = mid-1;
		}
		printf ("%d\n", ss[ret+1]);
		x = ss[ret+1];
	}
	return 0;
}
