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

const int M = 200000+10 ;
char s[M] , t[M<<1] ;
int lens , lent ;
int table[26] ;
int pal[M<<1] ;

void solve () {
	int maxn = 0 , id = 0 ;
	for (int i = 1 ; i < lent ; i ++) {
		int tmp = (2*pal[i]-1)/2 ;
		if (tmp < 2) continue ;
		if (tmp>maxn) {
			maxn = tmp ;
			id = i ;
		}
	}
	if (maxn==0) {
		puts ("No solution!") ;
		return ;
	}
	//printf ("pal[%d]=%d\n", id , pal[id]) ;
	printf ("%d %d\n" , (id-pal[id]+2)/2-1 , (id+pal[id]-2)/2-1) ; 
	for (int i=(id-pal[id]+2)/2-1;i<=(id+pal[id]-2)/2-1;i++) {
		printf ("%c",'a'+table[s[i]-'a']) ;
	} puts ("") ;
}

void manacher () {
	lens = strlen (s) ;
	lent = 0 ;
	t[lent++]='$' , t[lent++]='#' ;
	for (int i = 0 ; i < lens ; i ++) {
		t[lent++] = s[i] ;
		t[lent++] = '#' ;
	}

	int mx = 0 , id = 0 ;
	for (int i = 1 ; i < lent ; i ++) {
		if (mx>i) pal[i] = pal[2*id-i]<mx-i?pal[2*id-i]:mx-i ;
		else pal[i]=1 ;
		while (t[i+pal[i]]==t[i-pal[i]]) pal[i]++ ;
		if (i+pal[i]>mx) {
			mx=i+pal[i] ;
			id = i ;
		}
	}
	solve () ;
}
int main () {
	char ch[2] ;
	while (~ scanf ("%s" , ch)) {
		for (int i = 0 ; i < 26 ; i ++) table[i] = i ;
		rotate (table , table+('z'-ch[0]+1) , table+26) ;

		scanf ("%s" , s) ;
		manacher () ;
	}
	return 0 ;
}
