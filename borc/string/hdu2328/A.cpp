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

char s[4001][201] ;
char t[201] ;
char key[201] ;
int len ;
int nxt[201] ;
int minn_len ;
int n ;

void get_nxt (int l , int r) {
	t[r-l] = '\0' ;
	len = r-l ;
	for (int i = 0 ; l < r ; i ++) t[i] = s[0][l++] ;
	nxt[0] = -1 ;
	for (int i = 1 , j = -1 ; i < len ; i ++) {
		while (j!=-1 && t[i]!=t[j+1]) j=nxt[j] ;
		nxt[i] = t[i]==t[j+1]?++j:-1 ;
	}
}

bool kmp (char *s) {
	int lens = strlen (s) ;
	for (int i = 0 , j = -1 ; i < lens ; i ++) {
		while (j!=-1 && s[i]!=t[j+1]) j=nxt[j] ;
		if (s[i]==t[j+1]) {
			++j ;
			if (j == len-1) return true ;
		}
	}
	return false ;
}

void solve () {
	int lens = strlen (s[0]) ;
	key[0] = '#' ;
	for (int i = minn_len ; i > 0 ; i --) {
		for (int j = 0 ; j + i <= lens ; j ++) { 
			get_nxt (j , j+i) ;
			bool flag = 1 ;
			for (int i = 1 ; i < n ; i ++) {
				flag = kmp(s[i]) ;
				if (!flag) break ;
			}
			if (flag && (key[0]=='#' || strcmp(t,key)<0)) 
				strcpy (key,t) ;
		}
		if (key[0]!='#') {
			puts (key) ;
			return ;
		}
	}
	puts ("IDENTITY LOST") ;
}

int main () {
	while (~ scanf ("%d" , &n)) { 
		if (!n) break ;
		minn_len = 201 ;
		for (int i = 0 ; i < n ; i ++) {
			scanf ("%s" , s[i]) ;
			int tmp = strlen (s[i]) ;
			minn_len = min (minn_len , tmp) ; 
		}
		solve () ;
	}
	return 0 ;
}
