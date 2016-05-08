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
int sign(double x){return x<-eps?-1:x>eps;}

char s[20] ;
ll num ;
ll pw10[20] ;
ll maxn ;

void dfs (ll cur,int deep,int pos) {
	//printf ("pos=%d\n" , pos) ;
	if (pos==-1) {
		maxn = min (maxn , cur) ;
		return ;
	}
	int ch = s[pos]-'0' ;
	for (int i=0 ; i<=9 ; i++) {
		if ( (cur*cur/pw10[deep]%10+2*cur*i%10)%10==ch) 
			dfs(i*pw10[deep]+cur,deep+1,pos-1) ;
	}
}

void solve () {
	maxn = INF ;
	int pos = strlen (s) ;
	for (int i=0 ; i<=9 ; i++) {
		if (i*i%10 == s[pos-1]-'0') 
			dfs (i,1,pos-2) ;
	}
	if (maxn==INF) puts ("None") ;
	else printf (LLD"\n" , maxn) ;
}

int main () {
	pw10[0] = 1 ;
	for (int i=1 ; i<15 ; i++) pw10[i] = pw10[i-1]*10 ;
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf (LLD, &num) ;
		sprintf (s , LLD , num) ;
		solve () ;
	}
	return 0 ;
}
