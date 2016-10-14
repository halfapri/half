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
ll pw[M];
struct Hash {
	ll h[M];
	int n;
	void build (char *s,int _n) {
		n=_n, h[0]=s[0];
		for (int i=1; i<n; i++) h[i] = h[i-1]*BAS + s[i];
	}
	ll get (int l,int r) {
		return (h[r] - h[l-1]*pw[r-l+1]%MOD + MOD) % MOD;
	}
} hash;

int main () {
	pw[0] = 1;
	for (int i=1; i<M; i++) pw[i] = pw[i-1]*BAS%MOD;
	return 0;
}
