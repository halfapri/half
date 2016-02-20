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

const int mod = (int)(1e9+7) ;
struct node {
	ll cnt ;
	ll sum ;
	ll sqsum ;
	node () {}
	node (int _cnt , int _sum , int _sqsum) : cnt(_cnt) , sum(_sum) , sqsum(_sqsum) {} 
} dp[20][7][7] ;

ll l , r ;
int digit[20] ;
ll pw10[20] ;

node calc (int pos , ll pre1 , ll pre2 , bool wild) {
	if (pos == -1) 
		return node (pre1&&pre2 , 0 , 0) ;
	if (!wild && ~dp[pos][pre1][pre2].cnt)
		return dp[pos][pre1][pre2] ;
	int f = wild?digit[pos]:9 ;
	node tmp , ans(0 , 0 , 0) ;

	for (int i = 0 ; i <= f ; i ++) {
		if (i == 7) continue ;
		tmp = calc (pos-1 , (pre1+i)%7 , (pre2*10+i)%7 , wild&(i==f)) ;
		ans.cnt += tmp.cnt ;
		ans.cnt %= mod ;
		ans.sum += tmp.sum + tmp.cnt*i%mod*pw10[pos]%mod;
		ans.sum %= mod ;

		ans.sqsum += tmp.sqsum + 2*(i*pw10[pos]%mod)*(tmp.sum)%mod ;
		ans.sqsum %= mod ;
		ans.sqsum += (i*pw10[pos]%mod)*(i*pw10[pos]%mod)%mod*tmp.cnt%mod ;
		ans.sqsum %= mod ;
	}
	if (!wild)
		dp[pos][pre1][pre2] = ans ;
	return ans ;
}

ll go (ll o) {
	int pos = 0 ;
	for (; o > 0 ; o /= 10 , pos ++) {
		digit[pos] = o % 10 ;
	}
	return calc (pos-1 , 0 , 0 , 1).sqsum ;
}

int main () {
	for (int i = 0 ; i < 20 ; i ++) {
		for (int j = 0 ; j < 7 ; j ++) {
			for (int k = 0 ; k < 7 ; k ++) {
				dp[i][j][k].cnt = -1 ;
			}
		}
	}
	pw10[0] = 1 ;
	for (int i = 1 ; i < 20 ; i ++) pw10[i] = pw10[i-1]*10%mod ;
	int T ;
	scanf ("%d" , &T) ;
	while (T --) {
		scanf (LLD LLD , &l , &r) ;
		printf (LLD "\n" , (go(r)-go(l-1)+mod)%mod) ;
	}
	return 0 ;
}


