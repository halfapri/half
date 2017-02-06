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

const int mod = (int)1e6+3;
const int M = (int)1e6+10;
ll n, k;

inline ll mul (ll a,ll b) {
	ll ret=0;
	for (; b; b>>=1) {
		if (b&1) ret = (ret+a)%mod;
		a = (a+a)%mod;
	}
	return ret;
}
inline ll mul2 (ll a,ll b) {
	ll ret=0;
	for (; b; b>>=1) {
		if (b&1) ret = (ret+a)%(mod-1);
		a = (a+a)%(mod-1);
	}
	return ret;
}
inline ll qkpow (ll a,ll b) {
	ll ret=1;
	for (; b; b>>=1) {
		if (b&1) ret=mul(ret,a);
		a=mul(a,a);
	}
	return ret;
}
inline ll inv (ll a) {
	ll ret=1;
	for (int i=mod-2; i; i>>=1) {
		if (i&1) ret=ret*a%mod;
		a=a*a%mod;
	}
	return ret;
}

ll getB (ll n,ll k,ll sum) {
	ll ans = ((mul2(n,k)+sum)%(mod-1)+(mod-1))%(mod-1);
	return qkpow (2, ans);
}

ll getA () {
	ll ret=1;
	for (ll f=qkpow(2,n), i=1; i<k; i++) {
		ret=ret*(f-i)%mod;
	}
	return ret;
}

int main () {
	scanf (LLD LLD, &n,&k);
	if (n<=62 && k>(1ll<<n)) printf ("1 1\n");
	else {
		ll sum=0;
		for (ll i=62,pre=0; i>=0; i--) {
			ll tmp=pre;
			pre <<= 1;
			if ((k-1)>>i & 1) {
				tmp ++, pre ++;
			}
			sum = (sum + mul2(i,tmp))%(mod-1);
		}
		ll B = getB(n,k-1, -sum);
		ll A = k>mod?0:mul(getA(),inv(qkpow(2,sum)));
		A = ((B-A)%mod+mod)%mod;
		printf (LLD" "LLD"\n", A, B);
	}
	return 0;
}
