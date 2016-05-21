#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
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
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
int sign(double x){return x<-eps?-1:x>eps;}

ll l , r ;
vector<ll> pt ;

ll dfs (ll x) {
	int y = lower_bound (pt.begin(),pt.end(),x)-pt.begin() ;
	ll z = pt[y] ;
	if (z == x) return (z+1)/2 ;
	z = pt[y-1] + 1;
	return x-z+1 + dfs(x-2*(x-z)-1) ;
}

int main () {
	ll x = 1 ;
	while (true) {
		pt.push_back (x) ;
		x = x*2+1 ;
		if (x > (ll)1e18) break ;
	}
	int CASE ;
	scanf ("%d" , &CASE) ;
	while (CASE --) {
		scanf (LLD LLD , &l , &r) ;
		l -- ;
		ll tmp[2] = {l==0?0:dfs (l) , dfs(r)} ;
		printf (LLD "\n" , tmp[1]-tmp[0]) ;
	}
	return 0 ;
}
