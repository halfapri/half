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
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
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

const int M = 30;
bitset<M>a[M];

int Gauss (int equ,int var) {
	int i, j, k;
	int max_r;
	int col;

	for (col=0, k=0; k<equ && col<var; k++, col++) {
		for (max_r=k, i=k; i<equ; i++) if (a[i].test(col)) {
			max_r=i; break;
		}
		if (max_r!=k) swap(a[k], a[max_r]);
		if (a[k].test(col)==false) {
			k--; continue;
		}
		for (i=k+1; i<equ; i++) {
			if (a[i].test(col)) {
				a[i] = a[i]^a[k];
			}
		}
	}
	for (i=k; i<equ; i++) if (a[i].test(col)) {
		return -1;
	}
	return var-k;
}

int qkpow(int x,int n) {
	int ret=1;
	for (; n; n>>=1) {
		if (n&1) ret=ret*x;
		x = x*x;
	}
	return ret;
}

int b[M];

int main () {
	int T;
	scanf ("%d", &T);
	while (T --) {
		int n;
		scanf ("%d", &n);
		for (int i=0; i<=n; i++) a[i].reset();
		for (int i=0; i<n; i++) scanf ("%d", b+i);
		for (int i=0,x; i<n; i++) {
			scanf ("%d", &x);
			if (x^b[i]) a[i].set(n);
		}
		int x, y;
		while (~scanf("%d%d",&x,&y) && x+y) {
			x --, y--;
			a[y].set(x);
		}
		for (int i=0; i<n; i++) a[i].set(i);
		int ans=Gauss(n,n);
		if (ans==-1) puts ("Oh,it's impossible~!!");
		else printf ("%d\n", qkpow(2,ans));
	}
	return 0;
}
