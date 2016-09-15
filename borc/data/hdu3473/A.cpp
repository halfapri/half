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
const int MOD=(int)1e9+21,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 100000+10;
int rt[M], ls[M*22], rs[M*22]; 
struct NODE {
	ll sum;
	int cnt;
	inline NODE operator + (const NODE &rhs) const {
		NODE ret = {sum+rhs.sum, cnt+rhs.cnt};
		return ret;
	}
	inline NODE operator - (const NODE &rhs) const {
		NODE ret = {sum-rhs.sum, cnt-rhs.cnt};
		return ret;
	}
} T[M*22];
struct PERSIST {
	int sz;
	int init () {sz=0; return sz++;}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz ++;
	}
	void build (int o,int l,int r) {
		T[o] = {0,0};
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x,int val) {
		if (l == r) {T[u].sum += val;T[u].cnt++;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x,val);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x,val);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int bins (int o,int u,int l,int r,int &k) {
		if (k>T[u].cnt-T[o].cnt) {k-=T[u].cnt-T[o].cnt;return -1;}
		if (l == r) return l;
		int mid = l+r>>1;
		int ret = bins (ls[o],ls[u],l,mid,k);
		if (~ret) return ret;
		return bins (rs[o],rs[u],mid+1,r,k);
	}
	NODE ask (int o,int u,int l,int r,int pr) {
		if (r<=pr)return T[u]-T[o];
		int mid = l+r>>1;
		NODE ret = ask (ls[o],ls[u],l,mid,pr);
		if (pr>mid) ret = ret + ask (rs[o],rs[u],mid+1,r,pr);
		return ret;
	}
} sgt;

//////////////////////////////////////////////////////////////////
int ss[M], sz, a[M], n, Q;
int get (int x) {
	return lower_bound (ss, ss+sz, x) - ss;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	int CASE;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		scanf ("%d", &n);
		sz = 0;
		for (int i=1; i<=n; i++) {
			scanf ("%d", a+i);
			ss[sz ++] = a[i];
		}
		sort (ss, ss+sz);
		sz = unique (ss, ss+sz) - ss;
		sgt.build (rt[0]=sgt.init(),0,sz-1);
		for (int t=1; t<=n; t++) {
			rt[t]=sgt.alloc(rt[t-1]);
			sgt.ins (rt[t-1],0,sz-1,rt[t],get(a[t]),a[t]);
		}
//////////////////////////////////////////////////////////////////
		scanf ("%d", &Q);
		printf ("Case #%d:\n", cas);
		while (Q --) {int l, r, x;
			scanf ("%d%d", &l, &r); l ++, r ++;
			x = (r-l+2)/2;
			x = sgt.bins (rt[l-1],rt[r],0,sz-1,x);
			NODE lhs = sgt.ask(rt[l-1],rt[r],0,sz-1,x);
			ll tmp = 1ll*lhs.cnt*ss[x]-lhs.sum;
			tmp += T[rt[r]].sum-T[rt[l-1]].sum-lhs.sum-
				1ll*(r-l+1-lhs.cnt)*ss[x];
			printf (LLD"\n", tmp);
		} puts ("");
	}
	return 0;
}
