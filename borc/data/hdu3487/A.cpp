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

const int M = 300000+10, nill=0;
int ls[M], rs[M], rt;
struct NODE {
	bool mk;
	int v, sz;
	unsigned fix;
	void mark (int o) {
		mk^=1; swap (ls[o], rs[o]);
	}
} T[M];

struct TREAT {
	int sz;
	inline void init () {
		T[0].mk=T[0].sz=0;T[0].fix=rand();
		ls[0]=rs[0]=0; rt=nill; sz=1;
	}
	inline int alloc (int v) {
		T[sz].mk=0, T[sz].sz=1, T[sz].v=v;
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
		if (a==nill) {o=b;return;}
		if (b==nill) {o=a;return;}
		if (T[a].fix > T[b].fix) {
			down (o=a); merge (rs[o],rs[a],b);
		} else {
			down (o=b); merge (ls[o],a,ls[b]);
		} 
		up (o);
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		o = alloc(mid);
		if (l==r) {T[o].fix=rand();return;}
		build (ls[o],l,mid-1);
		build (rs[o],mid+1,r);
		T[o].fix = max (T[ls[o]].fix ,T[rs[o]].fix);
		T[o].sz += T[ls[o]].sz+T[rs[o]].sz;
	}
	void CUT (int l,int r,int x) {
		int a,b,c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		merge (rt, a, c);
		cut (rt, a, c, x);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
	void FLIP (int l,int r) {
		int a,b,c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mark (b);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
} my;

int n, m;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand (time(0));
	while (~ scanf ("%d%d", &n, &m) && n>0) {
		my.init ();
		my.build (rt, 1, n);
		while (m --) {char s[10]; int l, r, x;
			scanf ("%s", s);
			if (s[0]=='C') {
				scanf ("%d%d%d", &l, &r, &x);
				my.CUT (l, r, x);
			} else {
				scanf ("%d%d", &l, &r);
				my.FLIP (l, r);
			}
		}
		for (int i=1, a; i<=n; i++) {
			my.cut (rt, a, rt, 1); 
			printf ("%d%c", T[a].v, " \n"[i==n]);
		}
	}
	return 0;
}
