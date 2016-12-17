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

int n , m ;
bool vis[100000] ;

void bfs () {
	queue<pair<int,int> > q ;
	q.push({n,0}) ;
	while (!q.empty()) {
		pair<int,int> ans = q.front() ; q.pop () ;
		if (ans.F == m) {
			printf ("%d\n" , ans.S) ;
			return ;
		}
		int tmp ;
		for (int i = 0 ; i < 2 ; i ++) {
			if (i) tmp = ans.F-1 ;
			else tmp = ans.F*2 ;
			if (tmp < 0 || tmp >= (int)1e5) continue ;
			if (vis[tmp]) continue ;
			vis[tmp] = 1 ;
			q.push({tmp,ans.S+1}) ;
		}
	}
}

int main () {
	cin >> n >> m ;
	bfs () ;
	return 0 ;
}
