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

int dp[10][4600] ;
int digit[10] ;
int A , B ;

int fun(int o) {
	int pos = 0 ;
	int ret = 0 ;
	for (; o > 0 ; o /= 10 , pos ++) {
		ret += (o%10)<<pos ;
	}
	return ret ;
}

int calc (int pos , int pre , bool wild) {
	if (pre < 0) return 0 ;
	if (pos == -1)
		return 1 ;
	if (!wild && dp[pos][pre]!=-1)
		return dp[pos][pre] ;
	int f = wild?digit[pos]:9 ;
	int ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		ret += calc (pos-1 , pre-(i<<pos) , wild&(i==f)) ;
	}

	if (!wild)
		dp[pos][pre] = ret ;
	return ret ;
}

int go (int o) {
	int pos = 0 ;
	for (; o > 0 ; o/=10 , pos ++) {
		digit[pos] = o%10 ;
	}
	return calc (pos-1 , fun(A) , 1) ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	memset (dp , -1 , sizeof(dp)) ;
	for (int cas = 1 ; cas <= T ; cas ++) {
		scanf ("%d%d" , &A , &B) ;
		printf ("Case #%d: %d\n" , cas , go(B)) ;
	}
	return 0 ;
}
