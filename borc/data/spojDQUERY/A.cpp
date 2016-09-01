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

const int M = 30000+10;
int ls[M*22], rs[M*22], rt[M*22];

struct PERSIST {
	int T[M*22], n;
	inline int init () { n=0; return newnode();}
	inline int newnode () { T[n]=0; return n++;}
	void build (int o,int l,int r) {
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=newnode(), l, mid);
		build (rs[o]=newnode() ,mid+1, r);
	}
	void ins (int o,int l,int r,int u,int x) {
		T[u] = T[o]+1;
		ls[u] = ls[o], rs[u] = rs[o];
		if (l == r) return;
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=newnode(),x);
		else ins (rs[o],mid+1,r,rs[u]=newnode(),x);
	}
	int ask (int l,int r,int u,int x) {
		if (l>=x) return T[u];
		int mid = l+r>>1, ret=0;
		if (x<=mid) ret += ask (l,mid,ls[u],x);
		ret += ask (mid+1,r,rs[u],x);
		return ret;
	}
} sgt;

int n, m;
map<int,int> mp;

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &n);
	sgt.build (rt[0]=sgt.init(), 1, n);
	for (int i=1, x; i<=n; i++) {
		scanf ("%d", &x);
		if (mp.count (x))
			sgt.ins (rt[i-1], 1, n, rt[i]=sgt.newnode(), mp[x]);
		else rt[i] = rt[i-1];
		mp[x] = i;
	}
	scanf ("%d", &m);
	while (m --) {int l, r;
		scanf ("%d%d", &l, &r);
		printf ("%d\n", r-l+1 - sgt.ask (1, n, rt[r], l));
	}
	return 0;
}
