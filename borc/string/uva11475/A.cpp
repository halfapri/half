#include <stdio.h>
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
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 200000+10;
char s[M];
int nxt[M];

int main () {
	while (~ scanf ("%s", s)) {
		int n = strlen (s);
		reverse (s, s+n);
		s[n++] = '#';
		int mid = n-1;
		for (; ;n ++) {
			int l = 2*mid-n;
			if (l<0) break ;
			s[n] = s[l];
		}
		s[n] = '\0';
		nxt[0] = -1;
		for (int i=1, j=-1; i<n; i++) {
			while (j!=-1 && s[i]!=s[j+1]) j=nxt[j];
			nxt[i] = s[i]==s[j+1]?++j:-1;
		}
		s[mid] = '\0';
		printf ("%s%s\n", s+mid+1, s+nxt[n-1]+1);
	}
	return 0;
}
