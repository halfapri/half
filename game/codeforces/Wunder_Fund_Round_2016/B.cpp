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

int n ;
int mp[55][55] ;
int a[55] ;
bool vis[55] ;

void dfs (int x) {
	for (int i = 1 ; i <= n ; i ++) {
		bool flag = 0 ;
		if (vis[i]) continue ;
		for (int j = 1 ; j <= n ; j ++) {
			if (vis[j] || i == j) continue ;
			if (mp[i][j] != x) {
				flag = 1 ;
				break ;
			}
		}
		if (!flag) {
			vis[i] = 1 ;
			a[i] = x ;
			dfs (x+1) ;
			return ;
		}
	}
}

int main () {
	cin >> n ;
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 1 ; j <= n; j ++) {
			scanf ("%d" , &mp[i][j]) ;
		}
	}

	for (int i = 1 ; i <= n ; i ++) {
		bool flag = 0 ;
		for (int j = 1 ; j <= n ; j ++) {
			if (i == j) continue ;
			if (mp[i][j] != 1) {
				flag = 1 ;
				break ;
			}
		}
		if (!flag) {
			a[i] = 1 ;
			vis[i] = 1 ;
			dfs (2) ;
			break ;
		}
	}
	for (int i = 1 ; i <= n ; i ++) printf ("%d " , a[i]) ; puts ("") ;
	return 0 ;
}
