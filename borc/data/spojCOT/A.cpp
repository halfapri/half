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
int ls[M*22], rs[M*22], rt[M*22];

struct PERSIST {
	int T[M*22], n;
	inline int init () { n = 0; return newnode();}
	inline int newnode () { T[n] = 0; return n++;}
	void build (int o,int l,int r) {
		if (l == r) return;
		int mid = l+r>>1;
		ls[o] = newnode(), rs[o] = newnode();
		build (ls[o],l,mid);
		build (rs[o],mid+1,r);
	}
	void ins (int o,int l,int r,int x) {
		int u = n-1;
		T[u] = T[o] + 1;
		if (l == r) return;
		int mid = l+r>>1;
		if (x <= mid) {
			ls[u] = newnode(); rs[u] = rs[o];
			ins (ls[o],l,mid,x);
		} else {
			ls[u] = ls[o]; rs[u] = newnode();
			ins (rs[o],mid+1,r,x);
		}
	}
	int ask (int l,int r,int u,int v,int a,int fa,int &k) {
		if (k > T[u]+T[v]-T[a]-T[fa]) {
			k -= T[u]+T[v]-T[a]-T[fa]; return -1;
		}
		if (l == r) return l;
		int mid = l+r>>1;
		int ret = ask (l,mid,ls[u],ls[v],ls[a],ls[fa],k);
		if (~ret) return ret;
		return ask (mid+1,r,rs[u],rs[v],rs[a],rs[fa],k);
	}
} sgt;

struct VC:vector<int> {
	void done () {
		sort(begin(),end());
		erase (unique(begin(),end()),end());
	}
	int get (int x) {
		return lower_bound (begin(),end(),x) - begin();
	}
} ss;
int anc[18][M], val[M], deep[M];
struct EDGE {
	int v, nxt;
}edge[M<<1];
int head[M], es;

void dfs (int o,int u,int dep) {
	deep[u] = dep;
	rt[u] = sgt.newnode();
	sgt.ins (rt[o],0,ss.size()-1,ss.get(val[u]));
	for (int i=head[u]; ~i; i=edge[i].nxt) { int v = edge[i].v;
		if (v == o) continue;
		anc[0][v] = u;
		for (int k=1; k<18;k++)
			anc[k][v] = anc[k-1][anc[k-1][v]];
		dfs (u, v, dep+1);
	}
}

int getlca (int u,int v) {
	if (deep[u]<deep[v]) swap (u, v);
	for (int k=0; k<18; k++) 
		if ((deep[u]-deep[v]) & 1<<k) u = anc[k][u];
	if (u == v) return u;
	for (int k=17; k>=0; k--) 
		if (anc[k][u] != anc[k][v]) u=anc[k][u], v=anc[k][v];
	return anc[0][u];
}

int n, m;

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d%d", &n, &m);
	ss.resize (n);
	for (int i=1; i<=n; i++) {
		scanf ("%d", val+i);
		ss[i-1] = val[i];
	}
	ss.done ();
	memset (head, -1, sizeof(head[0])*(n+1));
	es = 0;
	for (int i=0; i<n-1; i++) { int u, v;
		scanf ("%d%d", &u, &v);
		edge[es] = {v, head[u]};
		head[u] = es ++; 
		edge[es] = {u, head[v]};
		head[v] = es ++;
	}
	sgt.build (rt[0]=sgt.init(), 0, ss.size()-1);
	dfs (0, 1, 0);
	while (m --) { int u, v, k;
		scanf ("%d%d%d", &u, &v, &k);
		int lca = getlca (u, v);
		//printf ("u=%d, v=%d, k=%d, lca=%d\n", u,v,k,lca);
		int ans = sgt.ask (0,ss.size()-1, 
				rt[u],rt[v],rt[lca],rt[anc[0][lca]],k);
		//printf ("ans=%d\n", ans);
		printf ("%d\n", ss[ans]);
	}
	return 0;
}
