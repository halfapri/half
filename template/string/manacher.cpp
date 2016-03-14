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
char s[M] , t[M<<1] ;
int lens , lent ;
int pal[M] ;

void manacher () {
	lens = strlen (s) ;
	lent = 0 ;
	t[lent ++] = '$' ;
	t[lent ++] = '#' ;
	for (int i = 0 ; i < lens ; i ++) {
		t[lent ++] = s[i] ; 
		t[lent ++] = '#' ;
	}
	t[lent] = '\0' ;

	int mx = 0 , id = 0 ;
	for (int i = 0 ; i < lens ; i ++) {
		if (mx > i) 
			pal[i] = pal[2*id-i] < mx-i ? pal[2*id-i] : mx-i ;
		else
			pal[i] = 1 ;

		while (t[i-pal[i]] == t[i+pal[i]]) 
			pal[i] ++ ;

		if (i+pal[i] > mx) {
			mx = i+pal[i] ;
			id = i ;
		}
	}
}

int main () {
	scanf ("%s" , s) ;
	manacher () ;
	return 0 ;
}
