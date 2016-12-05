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

const int mod = (int)1e9+7, M = 1000000+10;
int pw[M], n, k, dp[M], sum[M]; 
ll pre[M];

int lower (ll x) {
	return upper_bound (pre, pre+n+1, x) - pre - 1;
}

inline void add (int &a,int b) {
	a += b; if (a<0) a+=mod; if (a>=mod) a-=mod;
}

int main () {
	pw[0] = 1, pre[0] = 0;
	for (int i=1; i<M; i++) pw[i] = pw[i-1]*2%mod;
	for (int i=1; i<M; i++) pre[i] = pre[i-1]+i;
	int CASE;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		scanf ("%d%d", &n,&k);
		int tot = lower ((pre[k]-1)/2);
		dp[k] = pw[tot];
		sum[k] = (sum[k-1]+pw[tot])%mod;
		int l=k;
		bool flag = 0;
		for (int i=k+1; i<=n; i++) {
			while (l<i && pre[i]-pre[l]>pre[l]) l++;
			if (l == i) {flag=1; break;}
			dp[i] = 0;
			add (dp[i], (sum[i-1]-sum[l-1])%mod);
			sum[i] = 0;
			add (sum[i], (sum[i-1]+dp[i])%mod);
		}
		add(dp[n], dp[n]);
		printf ("Case #%d: %d\n", cas, flag?0:dp[n]);
	}
	return 0;
}
