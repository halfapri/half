#include<stdio.h>
#include<string.h>
#include<algorithm>
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

const int bas[2] = {17,233} ;
const int mod[2] = {(int)1e9+7 , (int)1e9+21} ;
const int M = 10000+10 ;
ll pw[M][2] ;

char s[M][76] ;
char t[M] ;
int nxt[M] ;
int row[M][2] , col[M][2] ;
int R , C ;

int get_hash (char *s , int x , int lens) {
	int ret = 0 ;
	for (int i=0 ; i<lens ; i ++) {
		ret = (ret + (s[i]-'a')*pw[i][x])%mod[x] ;
	}
	return ret ;
}

void get_col (int x) {
	for (int i=0 ; i<R ; i++) 
		t[i] = s[i][x] ;
	col[x][0] = get_hash (t , 0 , R) ;
	col[x][1] = get_hash (t , 1 , R) ;
}

void get_nxt (int s[M][2] , int lens) {
	nxt[0] = -1 ;
	for (int i=1 , j=-1 ; i<lens ; i++) {
		while (j!=-1 && (s[i][0]!=s[j+1][0]||s[i][1]!=s[j+1][1])) j=nxt[j] ;
		nxt[i] = (s[i][0]==s[j+1][0]&&s[i][1]==s[j+1][1])?++j:-1 ;
	}
}

int main () {
	pw[0][0] = pw[1][0] = 1 ;
	for (int i=1 ; i<M ; i++) {
		pw[i][0] = (pw[i-1][0]*bas[0])%mod[0] ;
		pw[i][1] = (pw[i-1][1]*bas[1])%mod[1] ;
	}

	while (~ scanf ("%d%d" , &R , &C)) {
		for (int i=0 ; i<R ; i ++) {
			scanf ("%s" , s[i]) ;
			row[i][0] = get_hash (s[i] , 0 , C) ;
			row[i][1] = get_hash (s[i] , 1 , C) ;
		}
		for (int i=0 ; i<C ; i ++) 
			get_col (i) ;
		

		get_nxt (row , R) ;
		int length = R-1-nxt[R-1] ;
		get_nxt (col , C) ;
		int wide = C-1-nxt[C-1] ;
		printf ("%d\n" , length*wide) ;
	}
	return 0 ;
}
