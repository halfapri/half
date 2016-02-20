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
int pw2[10] ;
int cnt = 0 ;
bool vis[5000] ;

void work(int o) {
	int pos = 0 ;
	int ret = 0 ;
	for (; o > 0 ; o/=10 , pos ++) {
		ret += (o%10)*pw2[pos] ;
	}
	if (vis[ret] == 0) {
		vis[ret] = 1 ;
		cnt ++ ;
	}
}

int main () {
	pw2[0] = 1 ;
	for (int i = 1 ; i < 10 ; i ++)
		pw2[i] = pw2[i-1]*2 ;
	for (int i = 0 ; i < (int)1e9 ; i ++) {
		work(i) ;
	}
	printf ("cnt = %d\n" , cnt) ;
	return 0 ;
}
