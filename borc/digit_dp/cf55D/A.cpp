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

ll dp[20][2520][49] ;
int digit[20] ;
int orm[2521] ;

void init () {
	int cnt = 0 ;
	for (int i = 1 ; i <= 2520 ; i ++) {
	   if (2520%i==0) orm[i] = cnt ++ ;
	}
}	

ll calc (int pos , int pre , int lcm , int wild ) {
	if (pos == -1) 
		return pre%lcm==0 ;
	if (!wild && dp[pos][pre][orm[lcm]]) 
		return dp[pos][pre][orm[lcm]] ;
	int f = wild?digit[pos]:9 ;
	ll ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		if (i == 0) 
			ret += calc (pos-1 , pre*10%2520 , lcm , wild&(i==f) ) ;
		else 
			ret += calc (pos-1 , (pre*10+i)%2520 , lcm*i/__gcd(lcm,i) , wild&(i==f) ) ;
	}
	if (!wild)
		dp[pos][pre][orm[lcm]] = ret ;
	return ret ;
}

ll go (ll x) {
	int pos = 0 ;
	while (x) {
		digit[pos ++] = x % 10 ;
		x /= 10 ;
	}
	return calc (pos-1 , 0 , 1 , 1) ;
}

int main () {
	init () ;
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		ll l , r ;
		scanf (LLD LLD , &l , &r) ;
		printf (LLD "\n" , go(r)-go(l-1)) ;
	}
	return 0 ;
}
