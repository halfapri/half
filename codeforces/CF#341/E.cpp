#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
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

const int MOD = (int)(1e9+7) ;
int cnt[20] ;
int n , b , k , x ;

struct Matrix {
	int n ;
	int mat[201][201] ; 
	Matrix () {} 
	Matrix (int _n) : n(_n) {//初始化为单位矩阵
		for (int i = 0 ; i < n ; i ++) {
			for (int j = 0 ; j < n ; j ++) {
				mat[i][j] = i == j ;
			}
		}	
	}

	inline void init_0 () {
		for (int i = 0 ; i < n ; i ++) {
			for (int j = 0 ; j < n ; j ++) {
				mat[i][j] = 0 ;
			}
		}
	}

	inline Matrix operator * (const Matrix &a) const {
		Matrix ans(n) ;
		for (int i = 0 ; i < n ; i ++) {
			for (int j = 0 ; j < n ; j ++) {
				ll res = 0 ;
				for (int k = 0 ; k < n ; k ++) {
					res += 1ll*mat[i][k]*a.mat[k][j] ;
					if (res > (ll)8e18) {
						res %= MOD ;
					}
				}
				ans.mat[i][j] = res % MOD ;
			}
		}
		return ans ;
	}

	inline Matrix operator ^ (int pw) const {
		Matrix res(n) ;
		Matrix x = *this ;
		for (; pw ; pw >>= 1) {
			if (pw&1) res = res*x ;
			x = x*x ;
		}
		return res ;
	}
} ;

void solve () {
	Matrix a(x) ;
	a.init_0 () ;
	for (int i = 0 ; i < x ; i ++) {
		for (int j = 1 ; j < 10 ; j ++) {
			a.mat[i][(i*10+j)%x] += cnt[j] ;  
		}
	}
	a = a^b ;
	printf ("%d\n" , a.mat[0][k]) ;
}

int main () {
	scanf ("%d%d%d%d" , &n , &b , &k , &x) ;
	for (int i = 0 ; i < n ; i ++) {
		int x ;
		scanf ("%d" , &x) ;
		cnt[x] ++ ;
	}
	solve () ;
	return 0 ;
}
