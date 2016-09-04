#include <stdio.h>
#include <bitset>
#include <string.h>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <math.h>
#include <queue>
#include <complex>
#include <functional>
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
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int inf = 0x3f3f3f3f ;
const ll INF = (ll)4e18 ;
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 1024+10;
int n;

struct SEGTREE {
	int T[M<<2][M<<2];
	void build (int o,int l,int r) {
		buildy (o,1,0,n-1);
		if (l == r) return;
		int mid = l+r>>1;
		build (lson); build (rson);
	}
	void buildy (int ox,int o,int l,int r) {
		T[ox][o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		buildy (ox,lson); buildy (ox,rson);
	}
	void ins (int o,int l,int r,int x,int y,int val) {
		insy (o,1,0,n-1,y,val);
		if (l == r) return;
		int mid = l+r>>1;
		if (x<=mid) ins (lson,x,y,val);
		else ins (rson,x,y,val);
	}
	void insy (int ox,int o,int l,int r,int y,int val) {
		if (l == r) {T[ox][o]+=val; return;}
		int mid = l+r>>1;
		if (y<=mid) insy (ox,lson,y,val);
		else insy (ox,rson,y,val);
		T[ox][o] = T[ox][o<<1] + T[ox][o<<1|1];
	}
	ll ask (int o,int l,int r,int xl,int xr,int yl,int yr) {
		if (xl<=l && r<=xr) return asky (o,1,0,n-1,yl,yr);
		int mid = l+r>>1;
		ll ret=0;
		if (xl<=mid) ret += ask (lson,xl,xr,yl,yr);
		if (xr>mid) ret += ask (rson,xl,xr,yl,yr);
		return ret;
	}
	ll asky (int ox,int o,int l,int r,int yl,int yr) {
		if (yl<=l && r<=yr) return T[ox][o];
		int mid = l+r>>1;
		ll ret=0;
		if (yl<=mid) ret += asky (ox,lson,yl,yr);
		if (yr>mid) ret += asky (ox,rson,yl,yr);
		return ret;
	}
} sgt;

int main () {
	//freopen ("read.txt", "r", stdin);
	int op;
	while (~ scanf ("%d", &op) && op!=3) {
		if (op == 0) {
			scanf ("%d", &n);
			sgt.build (1,0,n-1);
		} else if (op == 1) {int x,y,val;
			scanf ("%d%d%d", &x, &y, &val);
			sgt.ins (1,0,n-1,x,y,val);
		} else  {int l,b,r,t;
			scanf ("%d%d%d%d", &l, &b, &r, &t);
			printf (LLD"\n", sgt.ask (1,0,n-1,l,r,b,t));
		}
	}
	return 0;
}
