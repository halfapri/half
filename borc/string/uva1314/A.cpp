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

const int M = 100000+10 ;
char s[M] ;
int lens ;

inline int add (int x) {
	return x>=lens?x-lens:x ;
}

int minway () {
	int i=0 , j=1 , k=0 ;
	while (i<lens && j<lens && k<lens) {
		if (s[add(i+k)]==s[add(j+k)]) k ++ ;
		else {
			if (s[i+k]<s[j+k]) j+=k+1 ;
			else i+=k+1 ;
			if (i==j) j ++ ;
			k = 0 ;
		}
	}
	return min(i,j) ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d%s" , &lens , s) ;
		printf ("%d\n" , minway ()) ;
	}
	return 0 ;
}
