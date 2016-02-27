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

const int M = 1000000+10 ;
char s[M] ;
int lens ;
int nxt[M] ;

void get_nxt () {
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=s[j+1]) j=nxt[j] ;
		nxt[i] = s[i]==s[j+1]?++j : -1 ;
	}
}

int main () {
	int cas = 1 ;
	while (~ scanf ("%d" , &lens)) {
		if (lens==0) break ;
		scanf ("%s" , s) ;
		get_nxt () ;
		printf ("Test case #%d\n" , cas ++) ;
		for (int i = 1 ; i < lens ; i ++) {
			int cycle = i-nxt[i] ;
			if ( (i+1)%cycle || cycle == i+1) continue ;
			printf ("%d %d\n" , i+1 , (i+1)/cycle) ;
		}
		puts ("") ;
	}
	return 0 ;
}
