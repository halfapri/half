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
const int mod = 10007;
int n;

inline void add (int &a,int b) {
	a += b;
	if (a>=mod) a-=mod;
}

inline mat mul (mat &a,mat &b) {
	mat ret(a.size(),vec(b[0].size()));
	for (int i=0; i<a.size(); i++)
		for (int j=0; j<b[0].size(); j++)
			for (int z=0; z<b.size(); z++)
				add (ret[i][j], a[i][z]*b[z][j]%mod);
	return ret;
}

int main () {
	int CASE; scanf ("%d", &CASE); for (int cas=1; cas<=CASE; cas++) {
		scanf ("%d", &n);
		mat a (4, vec(1));
		a[0][0] = 1;
		mat ans (4, vec(4));
		for (int i=0; i<4; i++) ans[i][i] = 1;
//////////////////////////////////////////////////////////////////
		mat b(4, vec(4));
		for (int fr=0; fr<4; fr++) {
			for (int to=0; to<4; to++) {
				int cnt = abs((fr&1)-(to&1))+abs((fr>>1)-(to>>1));
				if (cnt==2) continue;
				if (cnt==1) b[to][fr] = 1;
				if (cnt==0) b[to][fr] = 2;
			}
		}
//////////////////////////////////////////////////////////////////
		for (int i=n; i; i>>=1) {
			if (i&1) ans = mul(ans, b);
			b = mul(b, b);
		}
		ans = mul(ans, a);
		printf ("%d\n", ans[0][0]);
	}
	return 0;
}
