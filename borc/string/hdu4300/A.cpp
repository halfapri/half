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

char con[26] , anticon[26] ;
const int M = 100000+10 ;
char s[M*2] , t[M] ;
int lent , lens ;
int nxt[M*2] ;

void get_nxt () {
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=s[j+1]) j=nxt[j] ;
		nxt[i] = s[i]==s[j+1]?++j:-1 ;
	}
}

void solve () {
	int j = nxt[lens-1] ;
	while (j!=-1) {
		if (j+1 <= lent/2) break ;
		j=nxt[j] ;
	}
	j = lent-(j+1) ;
	for (int i = 0 ; i < 26 ; i ++) {
		anticon[con[i]-'a'] = 'a'+i ;
	}
	for (int i = 0 ; i < j ; i ++) printf ("%c" , s[i]) ;
	for (int i = 0 ; i < j ; i ++) printf ("%c" , anticon[s[i]-'a']) ;
	puts ("") ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%s%s" , con , s) ;
		lent = strlen (s) ;
		for (int i = 0 ; i < lent ; i ++) {
			t[i] = con[s[i]-'a'] ;
		}
		lens = 2*lent ;
		strcat (s , t) ;
		get_nxt () ;
		solve () ;
	}
	return 0 ;
}
