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

char s[1000000+10] , t[10000+10] ;
int lens , lent ;
int nxt[10000+10] ;

void get_nxt () {
	lent = strlen (t) ;
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < lent ; i ++) {
		while (j!=-1 && t[i]!=t[j+1]) j=nxt[j] ;
		nxt[i] = t[i]==t[j+1]?++j:-1 ;
	}
}

void kmp () {
	get_nxt () ;
	lens = strlen (s) ;
	int cnt = 0 ;
	for (int i = 0 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=t[j+1]) j=nxt[j] ;
		if (s[i]==t[j+1]) {
			j ++ ;
			if (j == lent-1) {
				cnt ++ ; 
				j = nxt[j] ;
			}
		}
	}
	printf ("%d\n" , cnt) ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%s%s" , t , s) ;
		kmp () ;
	}
	return 0 ;
}
