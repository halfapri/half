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

const ll mod = (ll)2e17+3;
typedef vector<ll> vec;
typedef vector<vec> mat;
int n;
ll lst[55];

inline void add (ll &a,ll b) {
	a += b; if (a<0) a+=mod; if (a>=mod) a-=mod;
}

inline ll mul (ll a,ll b) {
	add (a,0), add (b,0);
	ll ret=0;
	for (; b; b>>=1) {
		if (b&1) add (ret, a);
		add (a, a);
	} return ret;
}

inline ll inv (ll a) {
	ll ret=1;
	for (ll i=mod-2; i; i>>=1) {
		if (i&1) ret = mul(ret,a);
		a = mul(a, a);
	} return ret;
}

void Gauss (mat &a) {
	int equ=SZ(a), var=SZ(a[0])-1;
	int i,j,k,col,max_r;
	ll tmp, ta, tb;

	for (k=col=0; k<equ && col<var; k++, col++) {
		for (max_r=k,i=k+1; i<equ; i++) if (a[i][col]>a[max_r][col]) {
			max_r=i;
		}
		if (max_r!=k) swap(a[max_r],a[k]);
		if (a[k][col]==0) {
			k--; continue;
		}
		tb = inv (a[k][col]);
		for (i=k+1; i<equ; i++) if (a[i][col]) {
			ta = inv (a[i][col]);
			for (j=col; j<var+1; j++) {
				a[i][j] = (mul(a[i][j],ta)-mul(a[k][j],tb))%mod;
				if (a[i][j]<0) a[i][j] += mod;
			}
		}
	}

	vec x(var);
	while (k!=var);
	for (i=k-1; i>=0; i--) {
		tmp = a[i][n];
		for (j=i+1; j<var; j++) if (a[i][j]) {
			add (tmp, -mul(a[i][j], x[j]));
		}
		x[i] = mul(tmp, inv(a[i][i]));
	}
	for (int i=0; i<var; i++) 
		printf (LLD"%c", x[i]>(ll)1e17?x[i]-mod:x[i], " \n"[i==var-1]);
}

int main () {
	int CASE; scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		scanf ("%d", &n);
		mat a(n, vec(n+1));
		for (int i=0; i<n; i++) scanf (LLD, lst+i);
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				ll tmp;
				scanf (LLD, &tmp);
				add (a[i][n], (-mul(lst[j],lst[j])+mul(tmp,tmp))%mod);
				add (a[i][j], (-2*lst[j]+2*tmp)%mod);
				lst[j] = tmp;
			}
		}
		printf ("Case %d:\n", cas);
		Gauss (a);
	}
	return 0;
}
