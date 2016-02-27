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

const int M = (int)(1e6+10) ;
char s[M] ;
int lens ;
int nxt[M] ;

void get_nxt () {
	lens = strlen (s) ;
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=s[j+1]) j = nxt[j] ;
		nxt[i] = s[i]==s[j+1]?++j:-1 ;
	}
}

int main () {
	while (~ scanf ("%s" , s)) {
		get_nxt () ;
		printf ("%d\n" , lens-1-nxt[lens-1]) ;
	}
	return 0 ;
}
