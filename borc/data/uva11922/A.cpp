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
struct NODE {
	int v,sz;
	bool mk;
	unsigned fix;
	inline void mark (int o) {
		mk^=1, swap(ls[o],rs[o]);
	}
} T[M];

struct TREAP {
	int sz, a, b, c;
	inline void init () {
		T[0].v=T[0].sz=T[0].mk=0;T[0].fix=rand();
		ls[0]=rs[0]=0;rt=nill;sz=1;
	}
	inline int alloc (int v) {
		T[sz].v=v, T[sz].sz=1, T[sz].mk=0, T[sz].fix=rand();
		ls[sz]=rs[sz]=nill; return sz++;
	}
	inline void up (int o) {
		T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
	}
	inline void down (int o) {
		if (T[o].mk) {
			if (ls[o]!=nill) T[ls[o]].mark(ls[o]);
			if (rs[o]!=nill) T[rs[o]].mark(rs[o]);
			T[o].mk=0;
		}
		T[o].sz = 1;
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k==0) {b=o,a=nill;return;}
		down (o);
		if (T[ls[o]].sz<k) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up (o);
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			down (o=a); merge (rs[o],rs[a],b); up (o);
		} else {
			down (o=b); merge (ls[o],a,ls[b]); up (o);
		}
	}
	void update (int l,int r) {
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mark (b);
		merge (rt, a, c);
		merge (rt, rt, b);
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		o = alloc (mid);
		if (l == r) return;
		build (ls[o],l,mid-1); build (rs[o],mid+1,r);
		up (o);
		T[o].fix = max(T[ls[o]].fix, T[rs[o]].fix);
	}
	void Print (int o) {
		if (o==nill) return;
		down (o);
		Print (ls[o]);
		printf ("%d\n", T[o].v);
		Print (rs[o]);
		up (o);
	}
} my;

int n, m;

int main () {
	srand (time(0));
	scanf ("%d%d", &n, &m);
	my.init();
	my.build (rt, 1, n);
	while (m --) {int l, r;
		scanf ("%d%d", &l, &r);
		my.update (l, r);
	}
	my.Print (rt);
	return 0;
}
