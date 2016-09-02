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
int rt[M];
int s[16];

struct TRIE {
	int go[M*17][2], T[M*17], n;
	int init () { n=0; return newnode();}
	inline int newnode () {T[n]=0; memset(go[n],0,8); return n++;}
	void ins (int pos,int o,int u) {
		T[u] = T[o]+1;
		go[u][0] = go[o][0], go[u][1] = go[o][1];
		if (pos==-1) return;
		ins (pos-1, go[o][s[pos]], go[u][s[pos]]=newnode());
	}
	int ask (int pos,int u,int v,int a,int fa) {
		if (pos==-1) return 0;
		int ret = 0, ch = !s[pos];
		if (T[go[u][ch]]+T[go[v][ch]]-T[go[a][ch]]-T[go[fa][ch]])
			ret = 1<<pos;
		else ch = s[pos];
		return ret + 
			ask (pos-1,go[u][ch],go[v][ch],go[a][ch],go[fa][ch]);
	}
} tr;

int n, m, val[M], deep[M], anc[18][M];
struct EDGE {
	int v,nxt;
} edge[M<<1];
int head[M], es;

void get (int x) {
	for (int i=0; i<16; i++, x>>=1) s[i] = x&1;
}

void dfs (int o,int u,int dep) {
	deep[u] = dep;
	rt[u] = tr.newnode();
	get (val[u]);
	tr.ins (15, rt[o], rt[u]);
	for (int i=head[u]; ~i; i=edge[i].nxt) { int v=edge[i].v;
		if (v == o) continue;
		anc[0][v] = u;
		for (int k=1; k<18; k++) 
			anc[k][v] = anc[k-1][anc[k-1][v]];
		dfs (u, v, dep+1);
	}
}

int getlca (int u,int v) {
	if (deep[u]<deep[v]) swap(u, v);
	for (int i=0; i<18; i++)
		if ((deep[u]-deep[v]) & 1<<i) u = anc[i][u];
	if (u == v) return u;
	for (int i=17; i>=0; i--)
		if (anc[i][u] != anc[i][v]) u=anc[i][u], v=anc[i][v];
	return anc[0][u];
}

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n, &m)) {
		rt[0] = tr.init ();
		for (int i=1; i<=n; i++) scanf ("%d", val+i);
		memset (head, -1, sizeof(head[0])*(n+1));
		es = 0;
		for (int i=1, u, v; i<n; i++) {
			scanf ("%d%d", &u, &v);
			edge[es] = {v, head[u]};
			head[u] = es ++;
			edge[es] = {u, head[v]};
			head[v] = es ++;
		}
		dfs (0, 1, 0);
		while (m --) {int x,y,z;
			scanf ("%d%d%d", &x, &y, &z);
			int lca = getlca (x, y);
			get (z);
			printf ("%d\n", 
				tr.ask(15,rt[x],rt[y],rt[lca],rt[anc[0][lca]]));
		}
	}
	return 0;
}
