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

const int M = 1e5+10 ;
int n ;
vector<int> vc ;

void dfs (int x) {
	int tmp = 1 ;
	for (int i = 1 ; i <= 20 ; i ++) {
		if (tmp >= x) {
			printf ("%d " , (tmp==x)?i:i-1) ;
			if (x != tmp) dfs (x-tmp/2) ;
			break ;
		}
		tmp *= 2 ;
	}
}

int main () {
	cin >> n ;
	int tmp = 1 ;
	for (int i = 1 ; i <= 20 ; i ++) {
		if (tmp >= n) {
			printf ("%d " , (tmp==n)?i:i-1) ; 
			if (n!=tmp) dfs (n-tmp/2) ;
			break ;
		}
		tmp *= 2 ;
	}
	return 0 ;
}
