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

const int mod=(int)1e9+7 ;
int n ;
int cnt[4] ;
string s ;

int qkpow (int a , int b) {
	int ret = 1 ;
	while (b) {
		if (b & 1) ret = 1ll*ret*a%mod ;
		b >>= 1 ;
		a = 1ll*a*a%mod ;
	}
	return ret ;
}

int main () {
	cin >> n >> s ;
	for (int i = 0 ; i < n ; i ++) {
		if (s[i]=='A') cnt[0] ++ ;
		else if (s[i]=='G') cnt[1] ++ ;
		else if (s[i]=='C') cnt[2] ++ ;
		else cnt[3] ++ ;
	}
	sort (cnt,cnt+4) ;
	if (cnt[3]==cnt[2]&&cnt[2]==cnt[1]&&cnt[1]==cnt[0]) {
		cout << qkpow(4,n) << endl ;
	}
	else if (cnt[3]==cnt[2]&&cnt[2]==cnt[1]) {
		cout << qkpow(3,n) << endl ;
	}
	else if (cnt[3]==cnt[2]) {
		cout << qkpow(2,n) << endl ;
	}
	else cout << 1 << endl ;
	return 0 ;
}
