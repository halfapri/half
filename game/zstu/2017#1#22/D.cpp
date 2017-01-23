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

const int M = 1000000+10;
int cnt[M][26];
char s[M], t[M];
ll n, m;

int main () {
	scanf (LLD LLD"%s%s", &n,&m,s,t);
	int ls = strlen(s), lt = strlen(t);
	int gcd = __gcd(ls,lt);
	ll lcm = 1ll*ls/gcd*lt;
	for (int i=0; i<ls; i++) cnt[i%gcd][s[i]-'a'] ++;
	ll ans=0;
	for (int i=0; i<lt; i++) ans += cnt[i%gcd][t[i]-'a'];
	printf (LLD"\n", n*ls/lcm*(lcm-ans));
	return 0;
}
