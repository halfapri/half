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

ull dp[20][1<<10][1<<10] ;
ull l , r ;
int digit[20] ;

bool judge (int o , int u) {
	for (int pos = 0 ; pos < 10 ; o >>= 1 , u >>= 1 , pos ++) {
		if (!(u&1)) continue ;
		if ( (o&1) == (pos&1) ) return false ; 
	}
	return true ;
}

ull calc (int pos , int bal , int vis , bool prezero , bool wild) {
	if (pos == -1)
		return judge (bal , vis) ;
	if (!wild && ~dp[pos][bal][vis])
	   return dp[pos][bal][vis] ;	
	int f = wild?digit[pos]:9 ;
	ull ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		if (i == 0 && prezero) 
			ret += calc (pos-1 , bal , vis , prezero , wild&(i==f)) ;
		else 
			ret += calc (pos-1 , bal^(1<<i) , vis|(1<<i) , 0 , wild&(i==f)) ;
	}
	if (!wild) 
		dp[pos][bal][vis] = ret ;
	return ret ;
}

ull go (ull o) {
	int pos = 0 ;
	for (; o > 0 ; o /= 10 , pos ++) {
		digit[pos] = o % 10 ;
	}
	return calc (pos-1 , 0 , 0 , 1 , 1 ) ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	memset (dp , -1 , sizeof(dp)) ;
	while (T --) {
		scanf ("%llu%llu" , &l , &r) ;
		printf ("%llu\n" , go(r)-go(l-1)) ;
	}
	return 0 ;
}
