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

const int M = 200000+10;
int ls[M*23], rs[M*23], rt[M], T[M*23], ss[M], sz;

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
	void ins (int o,int l,int r,int u,int x) {
		if (l == r) {T[u]++;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int binsy (int o,int u,int l,int r,int pl,int &k) {
		if (l>=pl && k>T[u]-T[o]) {k-=T[u]-T[o];return -1;}
		if (l == r) return k==T[u]-T[o]?l:-2;
		int mid = l+r>>1, ret=-1;
		if (pl<=mid) ret = binsy (ls[o],ls[u],l,mid,pl,k);
		if (~ret) return ret;
		return binsy (rs[o],rs[u],mid+1,r,pl,k);
	}
	int ask (int o,int u,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[u]-T[o];
		int mid = l+r>>1, ret = 0;
		if (pl<=mid) ret += ask (ls[o],ls[u],l,mid,pl,pr);
		if (pr>mid) ret += ask (rs[o],rs[u],mid+1,r,pl,pr);
		return ret;
	}
} sgt;

typedef pair<int,int> pii;
int n, b[10];
pii a[M];

bool solve () {
	//for (int i=2; i>=0; i--) {
	//	for (int j=0; j<3; j++) {
	//		printf ("%d ", b[i*3+j]);
	//	} puts ("");
	//}puts ("");
	auto binsx = [&](int beg,int sum) {
		int ret=0;
		for (int i=18; i>=0; i--) { 
			ret += 1<<i;
			if (ret>=sz || T[rt[ret]]-T[rt[beg]]>sum) 
				ret -= 1<<i;
		}
		if (T[rt[ret]]-T[rt[beg]] != sum) return -1;
		return ret;
	};
	int x[2]; 
	x[0] = binsx (0,b[0]+b[1]+b[2]);
	if (x[0]==-1) return false;
	x[1] = binsx (x[0],b[3]+b[4]+b[5]);
	if (x[1]==-1) return false;
	//printf ("%d %d\n", ss[x[0]],ss[x[1]]);
//////////////////////////////////////////////////////////////////
	int y[2], tmp;
	y[0] = sgt.binsy (rt[0],rt[sz-1],0,sz-1,0,tmp=b[0]+b[3]+b[6]);
	if (y[0]<0) return false;
	y[1] = 
		sgt.binsy(rt[0],rt[sz-1],0,sz-1,y[0]+1,tmp=b[1]+b[4]+b[7]);
	if (y[1]<0) return false;
	//printf ("%d %d\n", ss[y[0]], ss[y[1]]);
//////////////////////////////////////////////////////////////////
	if (sgt.ask(rt[0],rt[x[0]],0,sz-1,0,y[0]) == b[0] &&
		sgt.ask(rt[0],rt[x[0]],0,sz-1,y[0]+1,y[1]) == b[1] &&
		sgt.ask(rt[x[0]],rt[x[1]],0,sz-1,0,y[0]) == b[3] &&
		sgt.ask(rt[x[0]],rt[x[1]],0,sz-1,y[0]+1,y[1]) == b[4]) {
		printf ("%.6f %.6f\n%.6f %.6f\n",
			ss[y[0]]+0.5,ss[y[1]]+0.5,ss[x[0]]+0.5,ss[x[1]]+0.5);
		return true;
	}
	return false;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d", &n)) {
		sz = 0;
		ss[sz++] = -inf;
		for (int i=0; i<n; i++) {
			scanf ("%d%d", &a[i].fi, &a[i].se);
			ss[sz++] = a[i].fi;
			ss[sz++] = a[i].se;
		}
		for (int i=0; i<9; i++) scanf ("%d", b+i);
		sort (ss, ss+sz);
		sz = unique (ss, ss+sz) - ss;
		sort (a, a+n, [](pii a,pii b) {
				if (a.se == b.se) return a.fi < b.fi;
				return a.se < b.se;
				});
//////////////////////////////////////////////////////////////////
		auto get = [&] (int x) {
			return lower_bound (ss, ss+sz, x) - ss;
		};
		sgt.build (rt[0]=sgt.init(),0,sz-1);
		for (int t=0, i=0; t+1<sz; ) {
			if (i==n) {t++;rt[t] = rt[t-1];}
			while (t+1<sz && ss[t+1]<=a[i].se) {
				t ++;
				rt[t] = rt[t-1];
			}
			while (i<n && a[i].se == ss[t]) {
				int lst = rt[t];
				rt[t] = sgt.alloc (rt[t]);
				sgt.ins (lst,0,sz-1,rt[t],get(a[i].fi));
				i ++;
			}
		}
//////////////////////////////////////////////////////////////////
		//printf ("sz=%d\n", sz);
		//printf ("T[rt[1]]=%d,T[rt[2]]=%d,T[rt[3]]=%d\n",
		//		T[rt[1]],T[rt[2]],T[rt[3]]);
		sort (b, b+9);
		bool flag = 0;
		int cnt = 0;
		do {
			flag = solve ();
		} while (!flag && next_permutation(b, b+9));
		if (!flag) puts ("-1");
	}
	return 0;
}
