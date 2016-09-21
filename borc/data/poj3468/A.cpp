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
#include <time.h>
using namespace std ;
typedef long long ll ;
typedef long double ld ;
typedef unsigned long long ull ;
#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld
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
const int MOD=(int)1e9+21,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 100000+10, nill=0;
int ls[M], rs[M], rt;
struct NODE {
	ll sum, add; 
	int sz;
	unsigned fix;
	inline void mark (ll lz) {
		sum += 1ll*sz*lz; add += lz;
	}
} T[M];
struct TREAP {
	int sz;
	void init () {T[0].sum=T[0].add=T[0].sz=0;T[0].fix=ran();sz=1;}
	inline int alloc () {
		ls[sz]=rs[sz]=0,T[sz].add=0,T[sz].sz=1,T[sz].fix=ran();
		return sz++;
	}
	inline void up (int o) {
		T[o].sum += T[ls[o]].sum + T[rs[o]].sum;
		T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
	}
	inline void down (int o) {
		if (T[o].add) {
			if (ls[o]!=nill) T[ls[o]].mark(T[o].add);
			if (rs[o]!=nill) T[rs[o]].mark(T[o].add);
			T[o].add = 0;
		}
		T[o].sum -= T[ls[o]].sum + T[rs[o]].sum;
		T[o].sz -= T[ls[o]].sz + T[rs[o]].sz;
	}
	inline unsigned ran () {
		static unsigned fix = 91250681;
		return fix += fix << 2 | 1;
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o = b;
		else if (b==nill) o = a;
		else if (T[a].fix > T[b].fix) {
			down (o = a);
			merge (rs[o], rs[a], b);
			up (o);
		} else {
			down (o = b);
			merge (ls[o], a, ls[b]);
			up (o);
		}
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a = o, b = nill; return;}
		if (k == 0) {a = nill, b = o;return;}
		down (o);
		if (T[ls[o]].sz<k) {
			cut (rs[o], rs[a=o], b, k - T[ls[o]].sz -1);
			up (a);
		} else {
			cut (ls[o], a, ls[b=o], k);
			up (b);
		}
	}
	void build (int &o,int x) {
		if (x==0) {o=nill;return;}
		if (x==1) {scanf (LLD, &T[o=alloc()].sum); return;}
		int mid = x>>1, l, r;
		build (l, mid); build (r, x-mid);
		merge (o, l, r);
	}
	ll ask (int l,int r) {
		int a, b, c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		ll ans = T[b].sum;
		merge (rt, a, b);
		merge (rt, rt, c);
		return ans;
	}
	void update (int l,int r,ll lz) {
		int a, b, c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mark (lz);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
} my;

int n, m;

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n, &m)) {
		my.init();
		my.build (rt, n);
		while (m --) {char op[10]; int l, r; ll val;
			scanf ("%s", op);
			if (op[0] == 'Q') {
				scanf ("%d%d", &l, &r);
				printf (LLD"\n", my.ask (l, r));
			} else {
				scanf ("%d%d"LLD, &l, &r, &val);
				my.update (l, r, val);
			}
		}
	}
	return 0;
}
