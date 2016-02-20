#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
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

int dp[8][10] ;
int digit[8] ;
int l , r ;

int calc (int pos , int lst , bool wild , bool flag) {
	if (pos == -1) 
		return !flag ;
	if (!wild && dp[pos][lst] != -1)
	   return flag?0:dp[pos][lst] ;
	int f = wild?digit[pos]:9 ;
	int ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		ret += calc (pos-1 , i , wild&(i==f) , (lst==6&&i==2)||flag||i==4) ;
	}

	if (!wild)
		dp[pos][lst] = ret ;
	return ret ;
}

int go (int x) {
	int pos = 0 ;
	while (x) {
		digit[pos ++] = x%10 ;
		x /= 10 ;
	}
	return calc (pos-1 , 0 , 1 , 0) ;
}

int main () {
	memset (dp , -1 , sizeof(dp)) ;
	while (~ scanf ("%d%d" , &l , &r) ) {
		if (l == 0) break ;
		printf ("%d\n" , go(r)-go(l-1)) ;
	}
	return 0 ;
}
