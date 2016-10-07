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
struct Edge {
	int v,nxt;
} e[M<<1];
int head[M], E;
int anc[18][M],tin[M],tout[M],rev[M],deep[M],tim;

void dfs (int o,int u) {
	deep[u] = deep[o]+1;
	tin[u] = ++tim;
	rev[tin[u]] = u;
	for (int i=head[u],v; ~i; i=e[i].nxt) {
		if ((v=e[i].v) == o) continue;
		anc[0][v] = u;
		for (int k=1; k<18; k++) anc[k][v]=anc[k-1][anc[k-1][v]];
		dfs (u, v);
	}
	tout[u] = tim;
}

int getlca (int u,int v) {
	if (deep[u]<deep[v]) swap(u,v);
	for (int k=17; k>=0; k--)
		if (deep[anc[k][u]]>=deep[v]) u=anc[k][u];
	if (u == v) return u;
	for (int k=17; k>=0; k--)
		if (anc[k][u]!=anc[k][v]) u=anc[k][u],v=anc[k][v];
	return anc[0][u];
}
//////////////////////////////////////////////////////////////////

int T[M<<2];
struct Segtree {
#define mid (l+r>>1)
	void build (int o,int l,int r) {
		T[o] = r-l+1;
		if (l == r) return;
		build (lson); build (rson);
	}
	void ins (int o,int l,int r,int x,int val) {
		if (l == r) {T[o]+=val;return;}
		if (x<=mid) ins (lson,x,val);
		else ins (rson,x,val);
		T[o] = T[o<<1] + T[o<<1|1];
	}
	int askl (int o,int l,int r,int pl,int pr) {
		if (pl>pr) return -1;
		if (pl<=l && r<=pr) {
			if (T[o]==0) return -1;
			if (l == r) return rev[l];
		}
		int ret=-1;
		if (pl<=mid) ret=askl(lson,pl,pr);
		if (ret==-1 && pr>mid) ret=askl(rson,pl,pr);
		return ret;
	}
	int askr (int o,int l,int r,int pl,int pr) {
		if (pl>pr) return -1;
		if (pl<=l && r<=pr) {
			if (T[o]==0) return -1;
			if (l == r) return rev[l];
		}
		int ret=-1;
		if (pr>mid) ret=askr(rson,pl,pr);
		if (ret==-1 && pl<=mid) ret=askr(lson,pl,pr);
		return ret;
	}
#undef mid
} sgt;

int n, m, q[M], Q;
bool vis[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	int CASE;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		scanf ("%d%d", &n, &m);
		E=tim=0;
		memset (head, -1, sizeof(head[0])*(n+1));
		for (int i=1,u,v; i<n; i++) {
			scanf ("%d%d", &u, &v);
			e[E] = {v,head[u]};
			head[u] = E++;
			e[E] = {u,head[v]};
			head[v] = E++;
		}
		dfs (0, 1);
		sgt.build (1, 1, tim);
		printf ("Case #%d:\n", cas);
		while (m --) {
			scanf ("%d", &Q);
			for (int i=0; i<Q; i++) scanf ("%d", q+i), vis[i]=false;
			sort (q, q+Q, [&](int a,int b) {
					return deep[a]>deep[b];
					});
			int ans = n - Q;
			for (int i=0; i<Q; i++) {
				int a = sgt.askl (1,1,tim,tin[q[i]]+1,tout[q[i]]);
				int b = sgt.askr (1,1,tim,tin[q[i]]+1,tout[q[i]]);
				//printf ("q=%d,a=%d,b=%d\n", q[i],a,b);
				if (a==b || getlca(a,b)!=q[i]) {
					sgt.ins (1,1,tim,tin[q[i]],-1); vis[i]=true;
				} else ans ++;
			}
			for (int i=0; i<Q; i++) if(vis[i]) sgt.ins(1,1,tim,tin[q[i]],1);
			printf ("%d\n", ans);
		}
	}
	return 0;
}
