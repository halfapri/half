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

const int M = (int)1e4+10 ;
int dp[101][M],a[101][M],n,m,X,T ;

struct NODE {
	int id,val ;
	NODE (int _id=0,int _val=0):id(_id),val(_val){}
} ;

void solve () {
	fill (dp[0]+1,dp[0]+1+m,-inf) ;
	dp[0][X] = 0 ;
	for (int i=1 ; i<=n ; i++) {
		deque<NODE> q ;
		for (int j=1 ; j<=m ; j++) {
			int tmp = dp[i-1][j] - a[i][j-1] ;
			while(!q.empty()&&tmp>q.back().val) q.pop_back();
			q.push_back (NODE(j,tmp)) ;
			while(!q.empty()&&q.front().id+T<j) q.pop_front();
			dp[i][j] = q.front().val + a[i][j];
		}
		while(!q.empty()) q.pop_back() ;
		for (int j=m ; j>=1 ; j--) {
			int tmp = dp[i-1][j] + a[i][j] ;
			while(!q.empty()&&tmp>q.back().val) q.pop_back();
			q.push_back(NODE(j,tmp)) ;
			while(!q.empty()&&q.front().id-T>j) q.pop_front();
			dp[i][j] = max(dp[i][j] , q.front().val-a[i][j-1])  ;
		}
	}
	int maxn = dp[n][1] ;
	for (int i=2 ; i<=m ; i++) maxn = max(maxn,dp[n][i]) ;
	printf ("%d\n" , maxn) ;
}

int main () {
	while (~scanf("%d%d%d%d",&n,&m,&X,&T)) {
		for (int i=1 ; i<=n ; i++)
			for (int j=1 ; j<=m ; j++) {
				scanf ("%d" , &a[i][j]) ;
				a[i][j] += a[i][j-1] ;
			}
		solve () ;
	}
	return 0 ;
}
