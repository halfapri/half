#include <stdio.h>
#include <time.h>
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
const int MOD=91250681,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 100000+10, nill=0;
int ls[M], rs[M], rt;
pair<int,int> ss[M];
int a[M], n;
struct NODE {
	int v, minn, sz;
	bool flip;
	unsigned fix;
	inline void mark (int o) {
		flip ^= 1;
		swap (ls[o], rs[o]);
	}
} T[M];

struct TREAP {
	int sz;
	void init () {
		T[0].minn=inf;T[0].sz=T[0].flip=T[0].fix=0;sz=1;
		ls[0] = rs[0] = nill;
	}
	inline unsigned ran () {
		static unsigned fix = 91250681;
		return fix += fix << 2 | 1;
	}
	inline int alloc () {
		T[sz].sz=1,T[sz].flip=0,T[sz].fix=ran();
		ls[sz]=rs[sz]=nill; return sz++;
	}
	inline void up (int o) {
		T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
		T[o].minn=min(T[o].minn,min(T[ls[o]].minn,T[rs[o]].minn));
	}
	inline void down (int o) {
		if (T[o].flip) {
			if (ls[o]!=nill) T[ls[o]].mark (ls[o]);
			if (rs[o]!=nill) T[rs[o]].mark (rs[o]);
			T[o].flip = 0;
		}
		T[o].sz -= T[ls[o]].sz + T[rs[o]].sz;
		T[o].minn = T[o].v;
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a = o, b = nill;return;}
		if (k==0) {b = o, a = nill;return;}
		down (o);
		if (T[ls[o]].sz<k) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut (ls[o],a,ls[b=o],k);
		up (o);
	}
	void merge (int &o,int a,int b) {
		if (a == nill) o = b;
		else if (b == nill) o = a;
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
	void build (int &o,int l,int r) {
		if (l == r) {T[o=alloc()].v=a[l];T[o].minn=a[l];return;}
		int mid = l+r>>1, lhs, rhs;
		build (lhs,l,mid); build (rhs,mid+1,r);
		merge (o,lhs,rhs);
	}
	void update (int l,int r) {
		int a, b, c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mark (b);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
	int ask (int o,int v) {
		if (T[o].v == v) return T[ls[o]].sz+1;
		down (o);
		int ret;
		if (T[ls[o]].minn <= v) ret = ask (ls[o],v);
		else ret = T[ls[o]].sz+1 + ask (rs[o],v);
		up (o);
		return ret;
	}
} my;

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d", &n) && n) {
		for (int i=0, v; i<n; i++) {
			scanf ("%d", &v);
			ss[i] = MP (v, i+1);
		}
		sort (ss, ss+n);
		for (int i=0; i<n; i++) a[ss[i].se] = i+1;
		my.init();
		my.build (rt, 1, n);
		for (int i=1, a; i<=n; i++) {
			int x = my.ask (rt, T[rt].minn);
			printf ("%d%c", x+i-1, (i==n?'\n':' '));
			my.update (1, x);
			my.cut (rt, a, rt, 1);
		}
	}
	return 0;
}
