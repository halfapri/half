#include <stdio.h>
#include <numeric>
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
#include <limits.h>
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
#define SZ(x) ((int)x.size())
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
#define sqr(x) ((x)*(x))
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int MOD=(int)1e9+7,BAS=233;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}
int AP (char *s) {
	unsigned hash=0;
	for(int i=0; s[i]; i++){
		if (i & 1) hash ^= (~((hash<<11)^s[i]^(hash>>5)));
		else hash ^= ((hash<<7)^s[i]^(hash>>3));
   } return hash & 0x7FFFFFFF;
}

const int M = 100000+10;
ll x[M], y[M];
int n, Q;
vector<int> g[M];
int pre[M];
int anc[18][M];
int deep[M];

inline bool better (ll ax,ll ay,ll bx,ll by) {
	return ay*bx<by*ax;
}

void dfs (int o,int u) {
	deep[u] = deep[o]+1;
	anc[0][u]=o;
	for (int i=1; i<18; i++) anc[i][u] = anc[i-1][anc[i-1][u]];
	for (int &v:g[u]) if (v!=o) {
		dfs (u, v);
	}
}

int getlca (int u,int v) {
	if (u==v) return u;
	if (deep[u]<deep[v]) swap(u,v);
	for (int i=17; i>=0; i--) 
		if (deep[anc[i][u]]>=deep[v]) u=anc[i][u];
	if (u==v) return u;
	for (int i=17; i>=0; i--) 
		if (anc[i][u] != anc[i][v]) u=anc[i][u], v=anc[i][v];
	return anc[0][u];
}

int main () {
	scanf ("%d", &n);
	for (int i=0; i<n; i++) scanf (LLD LLD, x+i, y+i);
	g[n-1].emplace_back (n-2);
	pre[n-2] = pre[n-1] = n-1;
	int id=n-1;
	for (int i=n-3; i>=0; i--) {
		int lst = i+1;
		int _lst = pre[lst];
		while (lst!=n-1 && 
			better(x[lst]-x[i],y[lst]-y[i],x[_lst]-x[i],y[_lst]-y[i])) {
			lst = _lst;
			_lst = pre[lst];
		}
		pre[i]=lst;
		g[lst].emplace_back (i);
	}
	dfs (n-1,n-1);
	int u, v;
	scanf ("%d", &Q);
	while (Q --) {
		scanf ("%d%d", &u,&v);
		printf ("%d\n", 1+getlca (--u,--v));
	}
	return 0;
}
