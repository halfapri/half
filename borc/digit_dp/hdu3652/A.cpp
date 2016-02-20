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

int dp[10][10][13][2] ;
int digit[10] ;
int r ;

int calc (int pos , int lst , int pre , bool flag , bool wild) {
	if (pos == -1)
		return !pre && flag ;
	if (!wild && dp[pos][lst][pre][flag] != -1) 
		return dp[pos][lst][pre][flag] ;
	int f = wild?digit[pos]:9 ;
	int ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		ret += calc (pos-1 , i , (pre*10+i)%13 , flag||(lst==1&&i==3) , wild&(i==f)) ;
	}
	if (!wild)
		dp[pos][lst][pre][flag] = ret ;

	return ret ;
}

int go (int o) {
	int pos = 0 ;
	while (o) {
		digit[pos ++] = o%10 ;
		o /= 10 ;
	}
	return calc (pos-1 , 0 , 0 , 0 , 1) ; 
}

int main () {
	memset (dp , -1 , sizeof(dp)) ;
	while (~ scanf ("%d" , &r)) {
		printf ("%d\n" , go(r)) ;
	}
	return 0 ;
}
