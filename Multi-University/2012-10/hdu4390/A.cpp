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
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

const int M = (int)1e6+10 ;
const int mod = (int)1e9+7;
int cnt[M],n;
int C[500][500] ;
int add (int a , int b) {
	a += b ;
	if (a<0) a+=mod ;
	return a>=mod?a-mod:a ;
}
void get_C () {
	C[0][0] = 1 ;
	for (int i=1 ; i<500 ; i++) {
		C[i][0] = 1 ;
		for (int j=1 ; j<=i ; j++) {
			C[i][j] = add(C[i-1][j-1],C[i-1][j]) ;
		}
	}
}
void get_cnt (int x) {
	for (int i=2 ; i*i<=x ; i++) {
		if (x%i == 0) {
			while (x%i == 0) cnt[i]++ , x/=i ;
		}
	}
	if (x!=1) cnt[x] ++ ;
}

void solve () {
	int ret = 0 ;
	vector<int> pt ;
	for (int i=1 ; i<= 1000000 ; i++) 
		if (cnt[i]) pt.push_back(cnt[i]) ;
	int sz = pt.size() ;
	for (int i=1 ; i<=n ; i++) {
		int ex = ((n-i)&1)?-1:1 ;
		int tmp = 1 ;
		for (int j=0 ; j<sz ; j++) {
			tmp = 1ll*tmp*C[pt[j]+i-1][i-1]%mod ;
		}
		ret = add(ret,1ll*C[n][i]*tmp%mod*ex) ;
	}
	printf ("%d\n" , ret) ;
}

int main () {
	get_C () ;
	while (~ scanf ("%d" , &n)) {
		memset (cnt , 0 , sizeof(cnt)) ;
		for (int i=0 ; i<n ; i++) {
			int x ;
			scanf ("%d" , &x) ;
			get_cnt (x) ;
		}
		solve () ;
	}
	return 0 ;
}
