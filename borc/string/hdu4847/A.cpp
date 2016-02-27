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

char t[5] = "doge" ;
char s[350000] ;
int lens ;
int nxt[5] ;
int cnt = 0 ;

void work () {
	lens = strlen (s) ;
	for (int i = 0 ; i < lens ; i ++) {
		if (s[i]>='A' && s[i]<='Z') 
			s[i] = s[i]-'A'+'a' ;
	}
	for (int i=0 , j=-1 ; i < lens ; i++) {
		while(j!=-1 && s[i]!=t[j+1]) j=nxt[j] ;
		if (s[i]==t[j+1]) {
			j ++ ;
			if (j==3) {
			   cnt ++ ;	
			   j = -1 ;
			}
		}
	}
}

int main () {
	memset (nxt , -1 , sizeof(nxt)) ;
	cnt = 0 ;
	while (~ scanf ("%s" , s)) {
		work () ;
	}
	printf ("%d\n" , cnt) ;
	return 0 ;
}
