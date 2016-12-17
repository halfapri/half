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

const int M = 200000+10;
typedef pair<int,int> pii;
vector<int> g[M];
int a[M], n;
bool flag;
ll maxnsum;
ll sum[M];

ll dfs (int o,int u) {
	sum[u] = a[u];
	vector<ll> ss;
	for (int v : g[u]) {
		if (v == o) continue;
		ss.emplace_back (dfs(u, v));
		sum[u] += sum[v];
	}
	sort (ALL(ss), [](ll a,ll b) {
			return a>b;
			});
	if (SZ(ss)>=2) {
		if (flag==false) maxnsum = ss[0]+ss[1], flag=true;
		else maxnsum = max(maxnsum, ss[0]+ss[1]);
	}
	return SZ(ss)==0?sum[u]:max(sum[u], ss[0]);
}

int main () {
	while (~scanf("%d", &n)) {
		for (int i=0; i<n; i++) scanf ("%d", a+i);
		for (int i=0; i<n; i++) g[i].clear();
		flag = 0;
		for (int i=0, u, v; i<n-1; i++) {
			scanf ("%d%d", &u, &v);
			u--, v--;
			g[u].emplace_back (v);
			g[v].emplace_back (u);
		}
		ll tmp = dfs (0, 0);
		if (!flag) puts ("Impossible");
		else printf (LLD"\n", maxnsum);
	}
	return 0;
}
