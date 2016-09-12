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
const int MOD=(int)1e9+7,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 200000+10;
ull pw[M];
struct HASH {
	ull h[M];
	int sz;
	void build (int n) {
		sz = n, h[0] = 0;
		for (int i=1, x; i<=n; i++) {
			scanf ("%d", &x);
			h[i] = h[i-1]*BAS + x;
		}
	}
	ull get (int l,int r) {
		return h[r] - h[l-1]*pw[r-l+1];
	}
} hs;

//////////////////////////////////////////////////////////////////
int n, m, K, a[M];
int rt[M], ls[M*30], rs[M*30], T[M*30];

struct PERSIST {
	int sz;
	int init () {sz=0;return sz++;}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz ++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x) {
		if (l == r) {T[u] ++; return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
	}
	bool ask (int o,int u,int l,int r,int x) {
		if (l == r) return T[u]-T[o]>0;
		int mid = l+r>>1;
		if (x<=mid) return ask (ls[o],ls[u],l,mid,x);
		else return ask (rs[o],rs[u],mid+1,r,x);
	}
} sgt;

//////////////////////////////////////////////////////////////////
int sz; 
ull ss[M];

int bins (ull x) {
	int y = lower_bound (ss, ss+sz, x) - ss;
	if (y == sz || x != ss[y]) return -1;
	return y;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	pw[0] = 1;
	for (int i=1; i<M; i++) pw[i] = pw[i-1]*BAS;
	while (~ scanf ("%d%d%d", &n, &m, &K)) {
		hs.build (n);
		sz = 0;
		for (int i=K; i<=n; i++) ss[sz ++] = hs.get(i-K+1,i);
		sort (ss, ss+sz);
		sz = unique (ss, ss+sz) - ss;
		sgt.build (rt[0]=sgt.init(),0,sz-1);
		for (int i=1; i<=n; i++) {
			rt[i] = rt[i-1];
			if (i>=K)  {
				rt[i] = sgt.alloc (rt[i-1]);
				sgt.ins(rt[i-1],0,sz-1,rt[i],bins(hs.get(i-K+1,i)));
			}
		}
//////////////////////////////////////////////////////////////////
		while (m --) {int x,y;ull tmp=0;
			scanf ("%d%d", &x, &y);
			for (int i=0, a; i<K; i++) {
				scanf ("%d", &a);
				tmp = tmp*BAS + a;
			} 
			x = x+K-1;
			int id = bins (tmp);
			if (x>y || id==-1) puts ("Yes");
			else {
				if(sgt.ask(rt[x-1],rt[y],0,sz-1,id))
					puts("No");
				else puts ("Yes");
			}
		}
	}
	return 0;
}
