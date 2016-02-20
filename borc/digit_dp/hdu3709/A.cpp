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

ll dp[20][20][1600] ;
int digit[20] ;
ll l , r ;

ll calc (int pos , int pivot , int torques , bool wild) {
	//cout << "pos = " << pos << " pivot = " << pivot << " torques = " << torques << endl ;
	if (pos==-1)
		return torques==0 ;
	if (!wild && dp[pos][pivot][torques]!=-1) 
		return dp[pos][pivot][torques] ;
	int f = wild?digit[pos]:9 ;
	ll ret = 0 ;

	for (int i = 0 ; i <= f ; i ++) {
		ret += calc (pos-1 , pivot , torques+i*(pos-pivot) , wild&(i==f)) ;
	}
	if (!wild)
		dp[pos][pivot][torques] = ret ;
	return ret ;
}

ll go (ll o) {
	int pos = 0 ;
	while (o) {
		digit[pos ++] = o%10 ;
		o /= 10 ;
	}
	ll ret = 0 ;
	for (int i = 0 ; i < pos ; i ++) { 
		ret += calc(pos-1 , i , 0 , 1) ;
	}
	return ret-pos ;
}

int main () {
	int T ;
	scanf ("%d" , &T) ;
	memset (dp , -1 , sizeof(dp)) ;
	while (T --) {
		scanf (LLD LLD , &l , &r) ;
		if (l) printf (LLD "\n" , go(r)-go(l-1)) ;
		else printf (LLD "\n" , go(r)+1) ;
	}
	return 0 ;
}
