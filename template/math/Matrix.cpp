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

typedef vector<int> vec;
typedef vector<vec> mat;
const int mod = (int)1e9 + 7;

void add (int &a,int b) {
	a += b; if (a<0) a+=mod; if (a>=mod) a-=mod;
}

inline mat mul (const mat &a,const mat &b) {
	mat ret(a.size(), vec(b[0].size()));
	for (int i=0; i<a.size(); i++)
		for (int j=0; j<b[0].size(); j++)
			for (int z=0; z<b.size(); z++)
				add (ret[i][j], 1ll*a[i][z]*b[z][j]%mod);
	return ret;
}
