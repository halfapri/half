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
const ll INF = (ll)4e18 ;

const int M = 1000000+10 ;
char s[M] ;
int exnxt[M] ;
int lens ;
int suf[M] ;

void solve () {
	suf[lens] = 0 ;
	for (int i=lens-1 ; i>=0 ; i--) {
		suf[i] = max(suf[i+1],i+exnxt[i]==lens?exnxt[i]:0) ;
	}

	int maxn = 0 ;
	for (int i=1 ; i<lens ; i ++) {
		int tmp = min (exnxt[i] , suf[i+1]) ;
		maxn = max (maxn , tmp) ;
	}
	printf ("%d\n" , maxn) ;
}

void get_exnxt () {
	lens = strlen (s) ;
	exnxt[0] = lens ;
	for (int i=1, a=0 , p=-1 ; i<lens ; i++) {
		if (i+exnxt[i-a]>p) {
			int j = max(0,p-i+1) ;
			while (i+j<lens && s[i+j]==s[j]) j ++ ;
			exnxt[i]=j ;
			a=i , p=i+exnxt[i]-1 ;
		}
		else exnxt[i] = exnxt[i-a] ;
	}
	
	solve () ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%s" , s) ;
		get_exnxt () ;
	}
	return 0 ;
}
