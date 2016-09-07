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
int ls[M*22], rs[M*22], T[M*22], rt[M];

struct PERSIST {
	int sz;
	int init () {sz=0; return alloc(0);}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=alloc(0),l,mid);
		build (rs[o]=alloc(0),mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x,int val) {
		if (l == r) {T[u]=val; return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x,val);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x,val);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	ll ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[o];
		int mid = l+r>>1;
		ll ret = 0;
		if (pl<=mid) ret += ask (ls[o],l,mid,pl,pr); 
		if (pr>mid) ret += ask (rs[o],mid+1,r,pl,pr);
		return ret;
	}
} sgt;

typedef pair<int,int> pii;
pii a[M];
int ss[M], sz, n, m;

int get (ll x) {
	return upper_bound (ss, ss+sz, x) - ss - 1;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	sz = 0;
	ss[sz ++] = -inf;
	for (int i=1; i<=n; i++) {
		scanf ("%d", &a[i].fi);
		a[i].se = i;
		ss[sz ++] = a[i].fi;
	}
	sort (a+1, a+n+1);
	sort (ss, ss+sz);
	sz = unique (ss, ss+sz) - ss;
	sgt.build (rt[0]=sgt.alloc(0),1,n);
	for (int t=1, i=1; t<sz; t++) {
		rt[t] = rt[t-1];
		while (i<=n && ss[t] == a[i].fi) {
			int lst = rt[t];
			sgt.ins (lst,1,n,rt[t]=sgt.alloc(lst),a[i].se,a[i].fi);
			i ++;
		}
	}
//////////////////////////////////////////////////////////////////
	scanf ("%d", &m);
	while (m --) {int pl, pr;
		scanf ("%d%d", &pl, &pr);
		ll ans = 1;
		while (true) {
			ll tmp = sgt.ask (rt[get(ans)],1,n,pl,pr);
			if (tmp < ans) break;
			else ans = tmp+1;
		}
		printf (LLD "\n", ans);
	}
	return 0;
}
