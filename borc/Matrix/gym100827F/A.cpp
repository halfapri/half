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
#include <complex>
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
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
int sign(double x){return x<-eps?-1:x>eps;}

typedef vector<int> vec ;
typedef vector<vec> mat ;
const int mod = (int)1e9+9 ;
int m , n ;

int judge (int x) {
	for (int i=0 ; i<m ; i++) {
		if ((x&1<<i)==0) continue ;
		if (i-2>=0 && (x>>m & 1<<i-2)) return 0 ;
		if (i+2<m && (x>>m & 1<<i+2)) return 0 ;
	}
	return 1 ;
}

int judge (int x,int y) {
	for (int i=0 ; i<m ; i++) {
		if ((y&1<<i)==0) continue ;
		if (i-1>=0 && (x>>m & 1<<i-1)) return 0 ;
		if (i+1<m && (x>>m & 1<<i+1)) return 0 ;
	}
	return 1 ;
}

void add (int &a , int b) {
	a += b ; if (a<0) a+=mod ;if(a>=mod) a-=mod ;
}

mat mul (const mat &a , const mat &b) {
	mat ret(a.size(),vec(b[0].size())) ;
	for (int i=0 ; i<a.size() ; i++)
		for (int j=0 ; j<b[0].size() ; j++)
			for (int z=0 ; z<b.size() ; z++)
				add (ret[i][j],1ll*a[i][z]*b[z][j]%mod) ;
	return ret ;
}

int main () {
	int CASE ;
	scanf ("%d" , &CASE) ;
	while (CASE --) {
		scanf ("%d%d" , &m , &n) ;
		mat a(1<<2*m , vec(1)) ;
		for (int i=0 ; i<a.size() ; i++) a[i][0] = judge(i) ;
		mat ans(a.size(),vec(a.size())) ;
		for (int i=0 ; i<a.size() ; i++) ans[i][i] = 1 ;
//////////////////////////////////////////////////////////////////
		mat b(a.size(),vec(a.size())) ;
		int full = (1<<m)-1 ;
		for (int i=0 ; i<a.size() ; i++) {
			if (judge(i)==0) continue ;
			for (int j=0 ; j<a.size() ; j++) {
				if( ((full&i)!=j>>m) || !judge(j) || !judge(i,j))
					continue ;
				b[j][i] = 1 ;
			}
		}
//////////////////////////////////////////////////////////////////
		if (n==1) printf ("%d\n",m==1?2:m==2?4:m==3?8:16) ;
		else {
			n -= 2 ;
			for (; n ; n>>=1) {
				if (n&1) ans = mul (ans , b) ;
				b = mul (b , b) ;
			}
			ans = mul (ans , a) ;
			int tot = 0 ;
			for (int i=0 ; i<ans.size() ; i++) add(tot,ans[i][0]);
			printf ("%d\n" , tot) ;
		}
	}
	return 0 ;
}
