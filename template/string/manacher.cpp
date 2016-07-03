#include <bits/stdc++.h>
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
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)1e18 ;

const int M = 100000+10 ;
char s[M] ;
int pal[M<<1] ;

void manacher () {
	int lens = strlen (s) ;
	int mx=0 , id=0 ;
	for (int i=0 , j; i<lens*2 ; i ++) {
		if (i>mx) j=1 ; else j=min(pal[2*id-i],mx-i) ;
		while (i-j>=0&&i+j<lens*2&&((i+j)&1 || s[i+j>>1]==s[i-j>>1])) j ++ ;
		pal[i] = j ;
		if (i+pal[i]>mx) mx=i+pal[i],id=i ;
	}
}
