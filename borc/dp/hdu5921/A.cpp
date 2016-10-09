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

const int mod = 1000000007;
ll n;
ll pw[80], pre[80];
int pos, digit[80];

int main () {
	pw[0] = 1;
	for (int i=1; i<80; i++) pw[i] = pw[i-1]*2%mod;
	int CASE;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		scanf (LLD, &n);
		pos = 0;
		for (ll x=n; x; x>>=1) digit[pos++] = x&1;
		pre[pos]=0;
		for (int i=pos-1; i>=0; i--) 
			pre[i] = (pre[i+1]*2%mod + digit[i])%mod;
		ll ans=0;
		n %= mod;
		for (int i=0; i<pos; i++) {
			ll fr = pw[i];
			ll to = pre[i+1];
			ans += (fr*(n+1-fr+mod)%mod)*to%mod;
			ans = (ans%mod+mod)%mod;
			if (digit[i]) {
				fr = (n-(pre[i]<<i)%mod+1+mod)%mod;
				ans += fr*(n+1-fr+mod)%mod;
				ans = (ans%mod+mod)%mod;
			}
		}
		printf ("Case #%d: "LLD"\n", cas, ans);
	}
	return 0;
}
