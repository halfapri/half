#include <stdio.h>
#include <bitset>
#include <string.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
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
#define sqr(x) ((x)*(x))
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
int sign(double x){return x<-eps?-1:x>eps;}

typedef vector<int> vec ;
typedef vector<vec> mat ;
int C[50][50] ,pw2[50];
const int mod = (int)1e9+7 ;
ll n ;
int k ;

inline void add (int &a , int b) { 
	a += b ; if(a<0) a+=mod ; if(a>=mod) a-=mod ;
}

mat mul (const mat &a , const mat &b) {
	mat ret(a.size(),vec(b[0].size())) ;
	for (int i=0 ; i<a.size() ; i++)
		for (int j=0 ; j<b[0].size() ; j++)
			for (int z=0 ; z<a[0].size() ; z++)
				add(ret[i][j] , 1ll*a[i][z]*b[z][j]%mod) ;
	return ret ;
}

int main () {
	for (int i=0 ; i<50 ; i++) { 
		C[i][0] = 1 ;
		for (int j=1 ; j<=i ; j++) 
			C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod ;
	}
	pw2[0] = 1 ;
	for (int i=1 ; i<50 ; i++) pw2[i] = (2*pw2[i-1])%mod ;
///////////////////////////////////////////////////////////////////
	scanf (LLD "%d" , &n , &k) ; k++ , n --;
	mat a(2*k+1,vec(1)) ;
	a[0][0] = 1 ;
	for (int i=k ; i<a.size() ; i++) a[i][0] = 1 ;
//////////////////////////////////////////////////////////////////
	mat ans(a.size(),vec(a.size())) ;
	for (int i=0 ; i<a.size() ; i++) ans[i][i] = 1 ;
//////////////////////////////////////////////////////////////////
	mat b(a.size(),vec(a.size())) ;
	for (int i=0 ; i<k ; i++) b[i][i+k] = 1 ;
	for (int i=k ; i<2*k ; i++) {
		int f=i-k ;
		for (int j=0 ; j<=f ; j++) 
			b[i][j] = 1ll*C[f][j]*pw2[f-j]%mod ;
		for (int j=k ; j<=k+f ; j++)
			b[i][j] = C[f][j-k] ;
	}
	for (int i=0 ; i<b.size() ; i++) b[b.size()-1][i] = b[b.size()-2][i] ;
	b[b.size()-1][b.size()-1] = 1 ;
//////////////////////////////////////////////////////////////////
	//for (int i=0 ; i<b.size() ; i++) {
	//	for (int j=0 ; j<b[0].size() ; j++) {
	//		printf ("%d " , b[i][j]) ;
	//	} puts ("") ;
	//} puts ("") ;
	for (; n ; n>>=1) {
		if (n&1) ans = mul(ans , b) ;
		b = mul (b , b) ;
	}
	ans = mul (ans , a) ;
	printf ("%d\n" , ans[ans.size()-1][0]) ;
	return 0 ;
}
