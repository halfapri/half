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

const int M = 200000+10 , mod = 10007 ;
char s[M] ;
int lens ;
int tot ;
int exnxt[M] ;

void get_exnxt () {
	tot = exnxt[0] = lens ;
	for (int i=1 , a=0 , p=-1 ; i < lens ; i ++) {
		if (i+exnxt[i-a]>p) {
			int j = max (0 , p-i+1) ;
			//printf ("(%d,%d),i=%d,j=%d\n" ,a , p, i , j) ;
			while (i+j<lens && s[j]==s[i+j]) j ++ ;
			tot += exnxt[i] = j , a = i ;
			p = exnxt[i]+i-1 ;
		}
		else tot += exnxt[i] = exnxt[i-a] ;
		if (tot >= mod) tot -= mod ;
	}
	//for (int i = 0 ; i < lens ; i ++) printf ("%d " , exnxt[i]) ;
	//puts ("") ;
	printf ("%d\n" , tot) ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d" , &lens) ;
		scanf ("%s" , s) ;

		get_exnxt () ;
	}
	return 0 ;
}
