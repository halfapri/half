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

const int M = 500000+10, mn = 500000;
int rt[M], ls[M*30], rs[M*30], T[M*30];

struct PERSIST {
	int sz;
	int init () {sz=0; return sz++;}
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
		if (l == r) {T[u] ++;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int ask (int o,int u,int l,int r,int &k) {
		if (k>T[u]-T[o]) {k -= T[u]-T[o]; return -1;}
		if (l == r) return l;
		int mid = l+r>>1;
		int ret = ask (ls[o],ls[u],l,mid,k);
		if (~ret) return ret;
		return ask (rs[o],rs[u],mid+1,r,k);
	}
	int Sum (int o,int u,int l,int r,int x) {
		if (r<=x) return T[u]-T[o];
		int mid = l+r>>1, ret = 0;
		ret += Sum (ls[o],ls[u],l,mid,x);
		if (x>mid) ret += Sum (rs[o],rs[u],mid+1,r,x);
		return ret;
	}
} sgt;

//////////////////////////////////////////////////////////////////
int rtx[M], s[20];
void makes (int x) {
	for (int i=0; i<20; i++, x>>=1) s[i] = x&1;
	reverse (s, s+20);
}

struct TRIE {
	int ls[M*30], rs[M*30], sz, T[M*30];
	int init () {sz=0; ls[0]=rs[0]=T[0]=0; return sz++;}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz ++;
	}
	void ins (int o,int u,int *s,int dep) {
		T[u] ++;
		if (dep == 20) return;
		if (*s == 0) ins (ls[o],ls[u]=alloc(ls[o]),s+1,dep+1);
		else ins (rs[o],rs[u]=alloc(rs[o]),s+1,dep+1);
	}
	int ask (int o,int u,int *s,int dep) {
		if (dep == 20) return 0;
		if (*s && T[ls[u]]-T[ls[o]]>0)
			return ask (ls[o],ls[u],s+1,dep+1);
		if (!*s && T[rs[u]]-T[rs[o]]>0)
			return (1<<19-dep) + ask (rs[o],rs[u],s+1,dep+1);
		if (T[ls[u]]-T[ls[o]]>0)
			return ask (ls[o],ls[u],s+1,dep+1);
		if (T[rs[u]]-T[rs[o]]>0)
			return (1<<19-dep) + ask (rs[o],rs[u],s+1,dep+1);
		return 0;
	}
} trie;

//////////////////////////////////////////////////////////////////
int m, tim;

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &m);
	sgt.build (rt[0]=sgt.init(),1,mn);
	rtx[0] = trie.init ();
	while (m --) {int op,x,l,r,k;
		scanf ("%d", &op);
		if (op == 0) {
			++tim;
			scanf ("%d", &x);
			rt[tim] = sgt.alloc (rt[tim-1]);
			sgt.ins (rt[tim-1],1,mn,rt[tim],x);
			makes (x);
			rtx[tim] = trie.alloc (rtx[tim-1]);
			trie.ins (rtx[tim-1],rtx[tim],s,0);
		} else if (op == 1) {
			scanf ("%d%d%d", &l, &r, &x);
			makes (x);
			printf ("%d\n", trie.ask (rtx[l-1],rtx[r],s,0));
		} else if (op == 2) {
			scanf ("%d", &k);
			tim -= k;
		} else if (op == 3) {
			scanf ("%d%d%d", &l, &r, &x);
			printf ("%d\n", sgt.Sum(rt[l-1],rt[r],1,mn,x));
		} else {
			scanf ("%d%d%d", &l, &r, &k);
			printf ("%d\n", sgt.ask(rt[l-1],rt[r],1,mn,k));
		}
	}
	return 0;
}
