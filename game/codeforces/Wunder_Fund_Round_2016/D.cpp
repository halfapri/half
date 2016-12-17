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

const int M = 2e5+10 ;
int dp[M][2] ;
vector<int> g[M] ;
int n , x , y ;

void dfs (int o , int u) {
	int tmp = 0 ;
	vector<int> diff ;
	for (int v : g[u]) {
		if (v == o) continue ;
		dfs (u , v) ;
		tmp += dp[v][0] ;
		diff.push_back (dp[v][1]-dp[v][0]+1) ;
	}
	diff.push_back (0) ; diff.push_back (0) ;
	swap(diff[0] , *max_element(diff.begin(),diff.end()));
	swap(diff[1] , *max_element(diff.begin()+1,diff.end())) ;
	dp[u][1] = tmp + diff[0] ;
	dp[u][0] = tmp + diff[0] + diff[1] ;
}

bool flag = 0 ;
int in[M] ;

void work () {
	if (!flag) printf (LLD "\n" , 1ll*(n-1)*y) ;
	else {
		printf (LLD "\n" , 1ll*x + 1ll*(n-2)*y) ;
	}
	exit (0) ;
}

int main () {
	scanf ("%d%d%d" , &n , &x , &y) ;
	for (int i = 0 ; i < n-1 ; i ++) {
		int u , v ;
		scanf ("%d%d" , &u , &v ) ;
		g[u].push_back (v) ;
		g[v].push_back (u) ;
		in[u] ++ ;
		in[v] ++ ;
		if (in[u]==n-1 || in[v]==n-1) flag = 1 ;
	}
	if (x > y) work () ;
	dfs (-1 , 1) ;
	printf (LLD "\n" , 1ll*dp[1][0]*x+1ll*(n-1-dp[1][0])*y) ;
	return 0 ;
}
