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

int a[1000000+10] , b[10000+10] ;
int nxt[10000+10] ;
int n , m ;

void get_nxt () {
	nxt[0] = -1 ;
	for (int i = 1 , j = -1; i < m ; i ++) {
	   if (j!=-1 && b[i]!=b[j+1]) j = nxt[j] ;	
	   nxt[i] = b[i]==b[j+1]?++j:-1 ;
	}
}

void kmp () {
	get_nxt() ;
	for (int i = 0 , j = -1 ; i < n ; i ++) {
		while (j!=-1 && a[i]!=b[j+1]) j = nxt[j] ;
		if (a[i] == b[j+1]) {
			j ++ ;
			if (j == m-1) {
				printf ("%d\n" , i-m+1+1) ;
				return ;
			}
		}
	}
	puts ("-1") ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d%d" , &n , &m) ;
		for (int i = 0 ; i < n ; i ++) scanf ("%d" , &a[i]) ;
		for (int i = 0 ; i < m ; i ++) scanf ("%d" , &b[i]) ;
		kmp () ;
	}
	return 0 ;
}
