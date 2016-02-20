#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)1e18 ;

ll dp[33][33][33] ;
int digit[33] ;
ll l , r ;

ll calc (int pos , int zeros , int head , bool wild) {
	if (pos == -1) 
		return zeros+zeros>=head+1 ; 
	if (!wild && dp[pos][zeros][head] != -1) 
		return dp[pos][zeros][head] ;
	int f = wild?digit[pos]:1 ;
	ll ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		if (i == 0)
			ret += calc (pos-1 , zeros+(pos!=head) , head-(pos==head) , wild&(i==f)) ;
		else 
			ret += calc (pos-1 , zeros , head , wild&(i==f)) ;
	}
	if (!wild)
		dp[pos][zeros][head] = ret ;
	return ret ;
}

ll go (ll o) {
	int pos = 0 ;
	while (o) {
		digit[pos ++] = o & 1 ;
		o >>= 1 ;
	}
	return calc (pos-1 , 0 , pos-1 , 1) ;
}

int main () {
	memset (dp , -1 , sizeof(dp)) ;
	while (~ scanf ("%I64d%I64d" , &l , &r)) {
		printf ("%I64d\n" , go(r)-go(l-1)) ;
	}
	return 0 ;
}
