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
template <class T> inline int SZ(T x){return (int)x.size();}

const int M = 100000+10;
vector<int> g[M];
vector<pair<int,int> >qu[M];
int ans[M], col[M], n, Q;

struct Node {
	map<int,int> col, ss;
	int sz;
	inline void ins (int x) {
		col[x] ++;
		ss[col[x]] ++;
		sz++;
	}
	inline void clr () { 
		col.clear(), ss.clear(), sz=0;
	}
	inline void swp (Node &x) { 
		swap(col,x.col), swap(ss,x.ss);
		swap(sz,x.sz);
	}
}T[M];

void Union (Node &x,Node &y) {
	if (x.sz<y.sz) x.swp(y);
	for (auto it=y.col.begin(); it!=y.col.end(); it++) {
		for (int i=0; i<it->se; i++) {
			x.ins (it->fi);
		}
	}
	y.clr();
}

void dfs (int o,int u) {
	T[u].sz=0;
	T[u].ins (col[u]);
	for (int &v: g[u]) {
		if (v==o) continue;
		dfs (u,v);
		Union (T[u], T[v]);
	}
	for (pair<int,int> &i:qu[u]) {
		ans[i.se] = T[u].ss[i.fi];
	}
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d%d", &n,&Q);
	for (int i=1; i<=n; i++) scanf("%d", col+i);
	for (int i=0,u,v; i<n-1; i++) {
		scanf("%d%d", &u,&v);
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	for (int i=0,v,k; i<Q; i++) {
		scanf ("%d%d", &v,&k);
		qu[v].emplace_back (k,i);
	}
	dfs (1,1);
	for (int i=0; i<Q; i++) printf ("%d\n", ans[i]);
	return 0;
}
