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
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
int sign(double x){return x<-eps?-1:x>eps;}

const int M = (int)5e6+10 ;
char s[M] ;
int pal[M<<1] ;
int dp[M<<1] ;

int main () {
	scanf ("%s" , s) ;
	int mx=0 , id=0 ;
	int lens = strlen (s) ;
	for (int i=0,j; i<2*lens ; i++) {
		if (i>mx) j=1 ; else j=min(pal[2*id-i],mx-i) ;
		while (i+j<2*lens&&i-j>=0&&((i+j)&1 || s[i+j>>1]==s[i-j>>1])) j++;
		pal[i] = j ;
		if (i+pal[i]>mx) mx=i+pal[i],id=i ;
	}
	ll ans = 1 ;
	dp[0] = 1 ;
	for (int i=1 ; i<2*lens ; i++) {
		if (!(i&1) && pal[i/2]==i/2+1) {
			dp[i] = dp[(i/2-1)/2*2]+1 ;
			//printf ("dp[%d]=%d\n" , i , dp[i]) ;
		}
		//if (!(i&1)) printf ("%c:%d\n" , s[i/2],(pal[i]+1)/2) ;
		ans = ans + dp[i] ;
	}
	printf (LLD "\n" , ans) ;
	return 0 ;
}
