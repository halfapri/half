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
#define fi first
#define se second
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

const ll mod = 1000000007 ;
int dp[62][3][3][3][3];
ll l , r , g , t ;
bool bit_g[62] , bit_t[62] ;
bool digit_l[62],digit_r[62] ;

inline int add (int a , int b) {
	a += b ;
	return a>=mod?a-mod:a ;
}

int get_steins (int x,int _x,int val) {
	if (x == 2) return 2 ;
	if (x == 0) return 0 ;
	if (_x<val) return 0 ;
	if (_x==val) return 1 ;
	if (_x>val) return 2 ;
}

int calc (int pos,int a,int b,int c,int d) {
	if (pos==-1) {
		return (a>=1 && c<=1) || (b>=1 && d<=1) ;
	}
	if (dp[pos][a][b][c][d]!=-1) return dp[pos][a][b][c][d] ;
	ll ret = 0 ;
	for (int i=0 ; i<2 ; i++) {
		int tmp[2] = {i^bit_g[pos],i^bit_t[pos]} ;
		int pt[4] = {get_steins(a,tmp[0],digit_l[pos]) , get_steins(b,tmp[1],digit_l[pos]) ,
			get_steins(c,tmp[0],digit_r[pos]) , get_steins(d,tmp[1],digit_r[pos])} ;
		ret = add (ret , calc(pos-1,pt[0],pt[1],pt[2],pt[3])) ;
	}
	return dp[pos][a][b][c][d] = ret;
}

void get_bit (bool a[62],ll x) {
	memset (a,0,sizeof(bool)*62) ;
	for (int i=0 ; x ; x/=2) a[i++] = x&1 ;
}

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	while (CASE--) {
		scanf (LLD LLD LLD LLD,&l,&r,&g,&t) ;
		get_bit(bit_g,g) ; get_bit(bit_t,t) ; get_bit(digit_l,l) ; get_bit(digit_r,r) ;
		memset (dp,-1,sizeof(dp)) ;
		printf ("%d\n" , calc(61,1,1,1,1)) ;
	}
	return 0 ;
}
