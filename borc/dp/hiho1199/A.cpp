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
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=91250681,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 10000+10;
vector<int> g[M];
int p[M], q[M], n;

void dfs (int o,int u) { 
	vector<int> id;
	for (int v:g[u]) if (v!=o) {
		dfs (u,v);
		id.emplace_back(v);
	}
	sort (ALL(id), [](int a,int b) {
			if (q[a]-p[a]>0 && q[b]-p[b]>0) return p[a]<p[b];
			if (q[a]-p[a]>0) return true;
			if (q[b]-p[b]>0) return false;
			return q[a]>q[b];
			});
	for (int v:id) {
		if (p[v]>q[u]) {
			p[u] += p[v]-q[u];
			q[u]=0;
		} else {
			q[u] -= p[v];
		}
		q[u] += q[v];
	}
	//printf ("p[%d]=%d, q[%d]=%d\n", u,p[u],u,q[u]);
}

int main () {
	scanf ("%d", &n);
	for (int i=1; i<=n; i++) scanf ("%d%d", p+i, q+i);
	for (int i=1,u,v; i<n; i++) {
		scanf ("%d%d", &u,&v);
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	dfs (1, 1);
	printf ("%d\n", p[1]);
	return 0;
}
