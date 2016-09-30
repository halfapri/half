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

const int M = 100000+10;
int tin[M], tout[M], tim, anc[18][M], revtin[M], deep[M];
ll path[M];
struct Edge {
	int u,v,w,nxt;
} e[M<<1];
int head[M], E;

void dfs (int o,int u) {
	tin[u] = ++tim;
	revtin[tin[u]] = u;
	for (int i=head[u], v; ~i; i=e[i].nxt) {
		if ((v=e[i].v) == o) continue;
		deep[v] = deep[u] + 1;
		path[v] = path[u] + e[i].w;
		anc[0][v] = u;
		for (int k=1; k<18; k++) anc[k][v] = anc[k-1][anc[k-1][v]];
		dfs (u, v);
	}
	tout[u] = tim;
}

int getlca (int u,int v) {
	if (deep[u]<deep[v]) swap(u,v);
	for (int i=17; i>=0; i--)
		if (deep[anc[i][u]]>=deep[v]) u=anc[i][u];
	if (u == v) return u;
	for (int i=17; i>=0; i--)
		if (anc[i][u] != anc[i][v]) u=anc[i][u], v=anc[i][v];
	return anc[0][u];
}

inline ll dist (int u, int v) {
	return path[u]+path[v]-2*path[getlca(u,v)];
}
//////////////////////////////////////////////////////////////////

struct Node {
	int a[2]; 
	ll d;
	inline void update (Node &x,int a0,int a1,ll d) {
		if (d<=x.d) return;
		x.a[0]=a0, x.a[1]=a1, x.d=d;
	}
	inline Node merge (Node rhs) {
		Node ret = d>rhs.d ? *this : rhs;
		for (int i=0; i<2; i++)
			for (int j=0; j<2; j++)
				update (ret, a[i], rhs.a[j], dist(a[i],rhs.a[j]));
		return ret;
	}
} T[M<<2];

struct Segtree {
#define mid (l+r>>1)
	void build (int o,int l,int r) {
		if (l == r) {
			T[o].a[0]=T[o].a[1]=revtin[l], T[o].d=0;
			return;
		}
		build (lson); build (rson);
		T[o] = T[o<<1].merge(T[o<<1|1]);
	}
	Node ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[o];
		if (pl<=mid && pr>mid)return ask(lson,pl,pr).merge(ask(rson,pl,pr));
		if (pl<=mid) return ask(lson,pl,pr);
		if (pr>mid) return ask(rson,pl,pr);
	}
#undef mid
} sgt;
//////////////////////////////////////////////////////////////////

int del[M], n, Q, I, DEL;
ll solve () {
	int beg = I;
	int l = tin[del[beg]];
	Node ans; ans.d=-1;
	ll ret=0;
	for (++I; I<DEL && tout[del[I]]<=tout[del[beg]];) {
		if (l<=tin[del[I]]-1) {
			if (ans.d==-1) ans = sgt.ask(1,1,tim,l,tin[del[I]]-1);
			else ans = ans.merge(sgt.ask(1,1,tim,l,tin[del[I]]-1));
		}
		l = tout[del[I]]+1;
		ret += solve ();
	}
	if (l<=tout[del[beg]]) {
		if (ans.d==-1) ans = sgt.ask(1,1,tim,l,tout[del[beg]]);
		else ans = ans.merge(sgt.ask(1,1,tim,l,tout[del[beg]]));
	}
	return ret + (ans.d==-1 ? 0 : ans.d);
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	memset (head, -1, sizeof(head[0])*(n+1));
	for (int i=1, u,v,w; i<n; i++) {
		scanf ("%d%d%d", &u, &v, &w);
		e[E] = {u,v,w,head[u]};
		head[u] = E++;
		e[E] = {v,u,w,head[v]};
		head[v] = E++;
	}
	dfs (0, 1);
	sgt.build (1, 1, tim);
	scanf ("%d", &Q);
	while (Q --) {int k;
		scanf ("%d", &k);
		DEL = 0;
		del[DEL++] = 1;
		for (int i=0, x; i<k; i++) {
			scanf ("%d", &x); x = x-1<<1;
			del[DEL++]=tin[e[x].u]<tin[e[x].v] ? e[x].v : e[x].u;
		}
		sort (del, del+DEL, [](int a,int b) {
				return tin[a] < tin[b];
				});
		I=0;
		printf (LLD"\n", solve ());
	}
	return 0;
}
