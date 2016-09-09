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

const int M = 500000+10, mn = 50000;
int ls[M*22], rs[M*22], rt[M];

struct NODE {
	int T[M*22], sz;
	int init () {sz=0; return sz++;}
	inline int alloc(int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz ++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz ++,l,mid);
		build (rs[o]=sz ++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x) {
		if (l == r) {T[u] = T[o]+1;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	bool ask (int u,int v,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[v]-T[u]>0;
		int mid = l+r>>1, ret=0;
		if (pl<=mid) ret += ask (ls[u],ls[v],l,mid,pl,pr);
		if (pr>mid) ret += ask (rs[u],rs[v],mid+1,r,pl,pr);
		return ret>0;
	}
} sgt;

struct POINT {
	int x, y;
	bool operator < (const POINT &rhs) {
		if (x == rhs.x) return y<rhs.y;
		return x<rhs.x;
	}
	bool operator == (const POINT &rhs) {
		return x==rhs.x && y==rhs.y;
	}
} a[M], b[M];
int n;

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d", &n) && n) {
		for (int i=0; i<n; i++) scanf ("%d%d", &a[i].x, &a[i].y);
		sort (a, a+n, [](POINT &lhs,POINT &rhs) {
				if (lhs.y==rhs.y) return lhs.x<rhs.x;
				return lhs.y<rhs.y;
				});
		n = unique (a, a+n) - a;
		for (int i=0; i<n; i++) b[i] = a[i];
		sort (b, b+n);
		sgt.build (rt[0]=sgt.init(),0,mn);
		for (int h=1, i=0; h<=mn; h++) {
			rt[h] = rt[h-1];
			while (i<n && h==a[i].y) {
				int lst = rt[h];
				sgt.ins (lst,0,mn,rt[h]=sgt.alloc(lst),a[i].x);
				i++;
			}
		}
//////////////////////////////////////////////////////////////////
		auto getb = [&] (POINT f) {
			int i = lower_bound (b, b+n, f) - b + 1;
			if (i==n || b[i].x != f.x) return mn;
			return b[i].y-1;
		};
//////////////////////////////
		bool flag = 0;
		for (int i=0; i<n && !flag; i++) {
			int v = getb (a[i]);
			int pl, pr;
			if (i==0 || a[i-1].y!=a[i].y) pl = 0;
			else pl = a[i-1].x+1;
			if (i==n-1 || a[i+1].y!=a[i].y) pr = mn;
			else pr = a[i+1].x-1;
			flag = sgt.ask (rt[a[i].y],rt[v],0,mn,pl,a[i].x-1) ||
				sgt.ask (rt[a[i].y],rt[v],0,mn,a[i].x+1,pr);
		}
		puts (flag ? "NO" : "YES");
	}
	return 0;
}
