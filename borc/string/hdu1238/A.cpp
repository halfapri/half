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

int nxt[111] , anti_nxt[111] ;
char t[111] , anti_t[111] ;
int len ;
char s[100][101] ;
int n ;

void get_nxt (char *t , int *nxt) {
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < len ; i ++) {
		while (j!=-1 && t[i]!=t[j+1]) j=nxt[j] ;
		nxt[i] = t[i]==t[j+1]?++j:-1 ;
	}
}

void get_t (int l , int r) {
	t[r-l] = '\0' ;
	len = r-l ;
	for (int i = 0 ; l < r ; i ++ , l ++)
		t[i] = s[0][l] ;
	strcpy (anti_t , t) ;
	reverse (anti_t , anti_t+len) ;
	get_nxt (t , nxt) ;
	get_nxt (anti_t , anti_nxt) ;
}

bool kmp (char *t , int *nxt , char *s) {
	int lens = strlen (s) ;
	for (int i = 0 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=t[j+1]) j=nxt[j] ;
		if (s[i]==t[j+1]) {
			j ++ ;
			if (j == len-1) return true ;
		}
	}
	return false ;
}

int solve () {
	int lens = strlen(s[0]) ;
	for (int i = lens ; i > 0 ; i --) {
		for (int j = 0 ; j+i<= lens; j ++) {
			get_t (j , j+i) ;
			//printf ("%s %s\n" , t , anti_t) ;
			bool flag = 0 ;
			for (int f = 1 ; f < n ; f ++) {
				if (kmp(t,nxt,s[f]) || kmp(anti_t,anti_nxt,s[f])) ;
				else {
					flag = 1 ;break ;
				}
			}
			if (!flag) return i ;
		}	
	}
	return 0 ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf ("%d" , &n) ;
		for (int i = 0 ; i < n ; i ++) 
			scanf ("%s" , s[i]) ;
		printf ("%d\n" , solve ()) ;
	}
	return 0 ;
}
