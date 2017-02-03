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

const int M = 500+10;
const ll inf = (ll)1e15;
int n;
ll g[M][M];
int x[M];
ll ans[M];
vector<int> a;

int main () {
	scanf ("%d", &n);
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			scanf (LLD, &g[i][j]);
		}
	}
	for (int i=0; i<n; i++) scanf ("%d", x+i);
	for (int cas=n-1; cas>=0; cas--) {
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=n; j++) {
				g[i][j] = min(g[i][j], g[i][x[cas]]+g[x[cas]][j]);
			}
		}
		a.emplace_back (x[cas]);
		for (int &v:a) {
			for (int &u:a) {
				ans[cas] += g[v][u];
			}
		}
	}
	for (int i=0; i<n; i++) printf (LLD"%c", ans[i]," \n"[i==n-1]);
	return 0;
}
