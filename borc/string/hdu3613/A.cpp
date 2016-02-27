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

const int M = 500000+10 ;
char s[M] , t[M<<1] ;
int lens , lent ;
int pal[M<<1] ;
int val[26] ;
int pre[M<<1] , suf[M<<1] ;

void solve () {
	pre[0] = suf[lent] = 0 ;
	for (int i = 1 ; i < lent ; i ++) 
		pre[i] = pre[i-1] + (t[i]=='#'?0:val[t[i]-'a']) ;
	for (int i = lent-1 ; i > 0 ; i --) 
		suf[i] = suf[i+1] + (t[i]=='#'?0:val[t[i]-'a']) ;

	//for (int i = 1 ; i < lent ; i ++)printf("%d ",pal[i]);puts("");
	int maxn = -inf ;
	for (int i = 2 ; i < lent-1 ; i ++) {
		int tmpl = 0 , tmpr = 0 ;
		if (t[i]=='#' && pal[(1+i)/2]==(1+i)/2)
			tmpl = pre[i] ;

		if (t[i]=='#' && pal[(i+lent-1)/2]==lent-(i+lent-1)/2) 
		   tmpr = suf[i] ;
		maxn = max (maxn , tmpl+tmpr) ;
	}
	printf ("%d\n" , maxn) ;
}

void manacher () {
	lens = strlen (s) ;
	lent = 0 ;
	t[lent++] = '$' ; t[lent ++] = '#' ;
	for (int i = 0 ; i < lens ; i ++) {
		t[lent++] = s[i] ;
		t[lent++] = '#' ;
	}

	int mx=0 , id=0 ;
	for (int i = 1 ; i < lent ; i ++) {
		if (mx>i) 
			pal[i] = pal[2*id-i]<mx-i?pal[2*id-i]:mx-i ;
		else
			pal[i] = 1 ;

		while (t[i+pal[i]] == t[i-pal[i]]) pal[i] ++ ;
		if (i+pal[i] > mx) {
			mx = i+pal[i] ;
			id = i ;
		}
	}

	solve () ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		for (int i = 0 ; i < 26 ; i ++)
			scanf ("%d" , &val[i]) ;
		scanf ("%s" , s) ;
		manacher () ;
	}
	return 0 ;
}
