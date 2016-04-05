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

const int M = (int)1e6+10 ;
int k , n ;
char s[M] ;
int flip[M][2] ;//0表示不翻，1表示翻
bool b[M] ;

void solve () {
	n = strlen(s) ;
	b[0] = s[0]=='B' ;
	for (int i=1 ; i<n ; i++)
		b[i] = s[i]!=s[i-1] ;
	for (int i=n-1 ; i>=0 ; i--) {
		int tmp[2] , c ;
		if (i+k>=n) {
			tmp[0]=0;
			tmp[1]=0;
			c=0 ;
		}
		else {
			tmp[0]=flip[i+k][0] ;
			tmp[1]=flip[i+k][1] ;
			c= b[i+k] ;
		}
		for (int j=0 ; j<2 ; j++)
			flip[i][j] = tmp[j^c]+j ;
	}
	int dp[2] ={flip[0][0],flip[0][1]}; //0表示-k+1,-k+2,……,i,……,0出现偶数次翻牌的最小方案数，
	//1表示-k+1,-k+2,……,i,……,0出现奇数次翻牌的最小方案数。
	for (int i=1 ; i<k&&i<=n ; i++) {
		int tmp[2]={inf,inf} ;
		for (int j=0 ; j<2 ; j++) //已经翻了偶数或奇数次
			for (int f=0 ; f<2 ; f++) //当前翻或不翻
				tmp[j^f]=min(tmp[j^f],dp[j]+f+flip[i][f^b[i]]) ;
		dp[0]=tmp[0] ;
		dp[1]=tmp[1] ;
	}
	printf ("%d\n" , b[0]?dp[1]:dp[0]) ;
}

int main () {
	int T ;
	scanf ("%d" ,&T) ;
	while (T --) {
		scanf ("%d%s" ,&k,s) ;
		if (k==1) {
			int cnt=0 ;
			for (int i=0 ; s[i] ; i++) if (s[i]=='B') cnt ++ ;
			printf ("%d\n" , cnt) ;
		}
		else solve () ;
	}
	return 0 ;
}
