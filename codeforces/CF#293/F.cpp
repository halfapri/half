#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define F first
#define S second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)1e18 ;

const int M = 2000+10 ;
int sumh[M][M] , sumv[M][M] ;
char s[M][M] ;
int n , m ;
ll ans[3] ;

ll get_turn0 () {
	ll ret = 0 ;
	for (int i = 2 ; i <= n-1 ; i ++) {
	   	if (sumh[i][m] == 0) ret ++ ;
	}
	for (int i = 2 ; i <= m-1 ; i ++) {
		if (sumv[n][i] == 0) ret ++ ;
	}
	return ret ;
}

ll get_turn1 () {
	ll ret = 0 ;
	for (int i = 2 ; i <= n-1 ; i ++) {
		for (int j = 2 ; j <= m-1 ; j ++) {
			if (!sumh[i][j]&&!sumv[i][j]) ret ++ ;
			if (!sumh[i][j]&&!(sumv[n][j]-sumv[i-1][j])) ret ++ ;
			if (!(sumh[i][m]-sumh[i][j-1])&&!sumv[i][j]) ret ++ ;
			if (!(sumh[i][m]-sumh[i][j-1])&&!(sumv[n][j]-sumv[i-1][j]))ret++;
		}
	}
	return ret ;
}

ll get_turn2 () {
	ll ret = 0 ;
	for (int i = 2 ; i <= n-1 ; i ++) {
		int two = 0 , one = 0 ;
		int des = 0 ;
		bool last[2]={} ;
		for (int j = 2 ; j <= m ; j ++) {
			if (s[i][j]=='#' || j==m) {
				ret += 1ll*4*two*(two-1)/2 + 1ll*one*(one-1)/2 + 1ll*2*one*two ;
				ret -= 1ll*des ;
				last[0] = last[1] = two = one = des = 0 ;
				continue ;
			}
			if (!sumv[i][j]&&!(sumv[n][j]-sumv[i-1][j])) {
				two++ ;
				if (last[0]) des ++ ;
				if (last[1]) des ++ ;
				last[0]=last[1] = 1 ;
			}
			else if (!sumv[i][j]) {
				one ++ ;
				if (last[0]) des ++ ;  
				last[0] = 1 , last[1] = 0 ;
			}
			else if (!(sumv[n][j]-sumv[i-1][j])) {
				one ++ ;
				if (last[1]) des ++ ;
				last[0] = 0 , last[1] = 1 ;
			}
			else last[0]=last[1]=0 ;
		}
	}
	for (int i = 2 ; i <= m-1 ; i ++) {
		int two = 0 , one = 0 ;
		int des = 0 ;
		bool last[2] = {} ;
		for (int j = 2 ; j <= n ; j ++) {
			if (s[j][i]=='#' || j==n) {
				ret += 1ll*4*two*(two-1)/2 + 1ll*one*(one-1)/2 + 1ll*2*one*two ;
				ret -= 1ll*des ;
				last[0] = last[1] = des = two = one = 0 ;
				continue ;
			}
			if (!sumh[j][i]&&!(sumh[j][m]-sumh[j][i-1])) {
				two++ ;
				if (last[0]) des ++ ;
				if (last[1]) des ++ ;
				last[0]=last[1] = 1 ;
			}
			else if (!sumh[j][i]) {
				one++ ;
				if (last[0]) des ++ ;
				last[0]=1 , last[1]=0 ;
			}
			else if (!(sumh[j][m]-sumh[j][i-1])) {
				one++ ;
				if (last[1]) des ++ ;
				last[0]=0 , last[1]=1 ;
			}
			else last[0]=last[1]=0;
		}
	}
	return ret ;
}

int main () {
	cin >> n >> m ;
	for (int i = 1 ; i <= n ; i ++) scanf ("%s" , s[i]+1) ;
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 1 ; j <= m ; j ++) {
			sumh[i][j] = sumh[i][j-1] + (s[i][j]=='#'?1:0) ; 
			sumv[i][j] = sumv[i-1][j] + (s[i][j]=='#'?1:0) ;
		}
	}

	ans[0] = get_turn0() ;
	ans[1] = get_turn1() ;
	ans[2] = get_turn2() ;
	//for (int i = 0 ; i < 3 ; i ++) printf ("ans[%d]=" LLD "\n" ,i , ans[i]) ;
	printf(LLD,ans[0]+ans[1]+ans[2]) ;
	return 0 ;
}
