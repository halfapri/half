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
typedef pair<int,int> pii;
vector<int> query[M];
int l[M], r[M], a[M], fa[M], vmax[M*10], result[M], n, Q;
vector<pii> ext[M];

int dsu (int x) {
	return fa[x] == x ? x : fa[x] = dsu (fa[x]);
}

struct BIT {
	int c[M], sz;
	void init (int n) {
		sz = n;
		memset (c, 0, sizeof(c[0])*(sz+1));
	}
	void update (int x,int val) {
		for (; x>0; x-=x&-x) c[x] += val;
	}
	int ask (int x,int ret=0) {
		for (; x<=sz; x+=x&-x) ret += c[x];
		return ret;
	}
} bit;

int main () {
	while (~ scanf ("%d%d", &n, &Q)) {
		for (int i=1; i<=n; i++) {
			scanf ("%d", a+i);
			query[i].clear ();
			ext[i].clear ();
		}
		for (int i=0; i<Q; i++) {
			scanf ("%d%d", l+i, r+i);
			query[r[i]].emplace_back (i);
		}
//////////////////////////////////////////////////////////////////
		iota (fa, fa+n+1, 0);
		for (int i=n; i>=1; i--) {
			ext[i].emplace_back (i, a[i]);
			for (int j=i+1, lst=i; j<=n; lst = j++) {
				j = dsu (j);
				a[j] = __gcd (a[j], a[lst]);
				if (a[j] == a[lst]) fa[lst] = j;
				else ext[lst+1].emplace_back (i, a[j]);
			}
		}
		memset (vmax, 0, sizeof(vmax));
		bit.init (n);
		for (int i=1, pl, gcd; i<=n; i++) {
			for (pii j: ext[i]) { tie (pl, gcd) = j;
				if (vmax[gcd]) bit.update (vmax[gcd], -1);
				vmax[gcd] = max(vmax[gcd], pl);
				if (vmax[gcd]) bit.update (vmax[gcd], 1);
			}
			for (int id: query[i]) {
				result[id] = bit.ask (l[id]);
			}
		}
		for (int i=0; i<Q; i++) printf ("%d\n", result[i]);
	}
	return 0;
}
