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

const int N = 200010 ;
struct point {
	int left , y , right ;
	point () {}
	point (int _left , int _y , int _right) :
		left(_left) , y(_y) , right(_right) {}
} info[N];
int minleft[N<<1] ;

void pushup (int o) {
	minleft[o] = min(minleft[o<<1] , minleft[o<<1|1]) ;
}

int query (int L , int R , int l , int r , int o) {
	if (l==r) {
		if (info[l].left<=L) return l ;
		return -1 ;
	}
	int mid = (l+r)>>1 , ans = -1 ;
	if (mid+1<=R && minleft[o<<1|1]<=L) 
	   ans = query (L, R, rson) ;	
	if (ans != -1) 
		return ans ;
	if (minleft[rt<<1] <= L) ans = query (L, R, lson) ;
	return ans ;
}

void modify (int pos , int l , int r , int o) {
	if (l==r) {
		minleft[o] = info[l].left ;
		return ;
	}
	int mid = (l+r)>>1 ;
	if (pos<=mid) modify (pos,lson) ;
	else modify (pos,rson) ;
	pushup(o) ;
}
