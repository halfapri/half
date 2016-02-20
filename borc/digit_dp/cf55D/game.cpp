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

int main () {
	int orm[49] ;
	int cnt = 0 ;
	for (int i = 1 ; i <= 2520 ; i ++) {
		if (2520%i == 0) orm[i] = cnt ++ ;
	}
	return 0 ;
}
