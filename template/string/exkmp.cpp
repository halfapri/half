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
char s[M] ;
int lens ;
int exnxt[M] ;

void get_exnxt () {
	lens = strlen (s) ;
	exnxt[0] = lens ;
	for (int i=1 , a=0 , p=-1 ; i<lens ; i ++) {
		if (i+exnxt[i-a]>p) {
			int j = max(0,p-i+1) ;
			while (i+j<lens && s[j]==s[i+j]) j ++ ;
			exnxt[i] = j ;
			a = i , p = exnxt[i]+i-1 ;
		}
		else 
			exnxt[i] = exnxt[i-a] ;
	}
}

int main () {
	scanf ("%s" , s) ;
	return 0 ;
}
