#include <stdio.h>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
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

struct VC:vector<int> {
	void done() {
		sort(begin(),end()) ;
		erase(unique(begin(),end()),end()) ;
	}
	int get (int x) {
		return lower_bound(begin(),end(),x)-begin() ;
	}
} ss ;

const int M = 100001+10 ;
struct CHAIR {
	int rt[M],ls[M*30],rs[M*30],T[M*30],oL;
	void build (int o,int l,int r) {
		oL = max(oL , o) ;
		T[o] = 0 ;
		ls[o] = o<<1 , rs[o] = o<<1|1 ;
		if (l==r) return ;
		int mid = l+r>>1 ;
		build(lson) ; build(rson) ;
	}
	void ins (int o,int lsto,int l,int r,int x) {
		if (l==r) { T[o] = T[lsto]+1 ; return ; }
		int mid = l+r>>1 ;
		if (x<=mid) {
			rs[o] = rs[lsto] ;
			ins (ls[o]=++oL , ls[lsto] , l , mid , x) ;
		} else {
			ls[o] = ls[lsto] ;
			ins (rs[o]=++oL , rs[lsto] , mid+1 , r , x) ;
		}
		T[o] = T[ls[o]] + T[rs[o]] ;
	}
	int kth (int lo,int ro,int l,int r,int &k) {
		if (T[ro]-T[lo] < k) { k -= T[ro]-T[lo] ; return -1 ; }
		if (l == r) return l ;
		int mid = l+r>>1 ;
		int ret = -1 ;
		ret = kth(ls[lo],ls[ro],l,mid,k) ;
		if (~ret) return ret ;
		ret = kth(rs[lo],rs[ro],mid+1,r,k) ;
		return ret ;
	}
} chair ;
int n , m ;
int a[M] ;

int main () {
	while (~ scanf ("%d%d" , &n,&m)) {
		ss.clear () ;
		for (int i=1 ; i<=n ; i++) {
			scanf ("%d" , a+i) ;
			ss.push_back (a[i]) ;
		}
		ss.done() ;
		chair.rt[0] = chair.oL = 1 ;
		chair.build(1,0,ss.size()-1) ;
		for (int i=1 ; i<=n ; i++) {
			chair.ins(chair.rt[i]=++chair.oL,chair.rt[i-1],0,ss.size()-1,ss.get(a[i])) ;
		} 
		while (m --) {int i,j,k ;
			scanf ("%d%d%d" , &i,&j,&k) ;
			int id = chair.kth(chair.rt[i-1],chair.rt[j],0,ss.size()-1,k);
			printf ("%d\n" , ss[id]) ;
		}
	}
	return 0 ;
}

