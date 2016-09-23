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

const int M = 200000+10, nill=0;
int ls[M], rs[M], fa[M], rt;
struct NODE {
	int l, r, sum, sz;
	unsigned fix;
} T[M];

struct TREAP {
	int sz;
	inline void init () {
		T[0].l=1,T[0].r=T[0].sum=T[0].sz=T[0].fix=0;
		ls[0]=rs[0]=fa[0]=0,sz=1,rt=nill;
	}
	inline int alloc (int l,int r) {
		T[sz].l=l,T[sz].r=r,T[sz].sum=r-l+1,T[sz].sz=1;
		T[sz].fix=rand();ls[sz]=rs[sz]=fa[sz]=nill;return sz++;
	}
	inline void up (int o) {
		T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
		T[o].sum += T[ls[o]].sum + T[rs[o]].sum;
		fa[ls[o]] = fa[rs[o]] = o;
	}
	inline void down (int o) {
		T[o].sz = 1;
		T[o].sum = T[o].r-T[o].l+1;
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
		if (T[a].fix>T[b].fix) {
			down (o=a); merge (rs[o],rs[a],b);
		} else {
			down (o=b); merge (ls[o],a,ls[b]);
		}
		up (o);
	}
	int askpos (int o) {
		if (o == rt) return 0;
		return (o==ls[fa[o]]?0:T[ls[fa[o]]].sz+1) + askpos(fa[o]);
	}
	int Rank (int o,int x) {
		if (x<=T[ls[o]].sum) return Rank (ls[o], x);
		if (x<=T[ls[o]].sum+T[o].r-T[o].l+1) 
			return x-T[ls[o]].sum+T[o].l-1;
		return Rank (rs[o], x-T[ls[o]].sum-(T[o].r-T[o].l+1));
	}
	int Query (int o) {
		if (o == rt) return 0;
		return (o==ls[fa[o]]?0:T[fa[o]].sum-T[rs[fa[o]]].sum) 
			+ Query (fa[o]);
	}
	void Top (int o) {
		int pos = askpos(o)+1+T[ls[o]].sz, a, b, c;
		cut (rt, a, b, pos-1);
		cut (b, b, c, 1);
		merge (a, a, c);
		merge (rt, b, a);
	}
} my;

int n, Q;
struct OP {
	char s[10];
	int x;
}op[M];
int ss[M], tt[M], sz;
int get (int x) {
	return tt[lower_bound (ss, ss+sz, x) - ss];
}

int main () {
	//freopen ("read.txt", "r", stdin);
	srand (time(0));
	int CASE;
	scanf ("%d", &CASE);
	for (int cas=1; cas<=CASE; cas++) {
		scanf ("%d%d", &n, &Q);
		sz = 0;
		ss[sz ++] = n;
		ss[sz ++] = 1;
		for (int i=0; i<Q; i++) {
			scanf ("%s%d", op[i].s, &op[i].x);
			if (op[i].s[0] == 'T' || op[i].s[0] == 'Q')
				ss[sz ++] = op[i].x;
		}
		sort (ss, ss+sz);
		sz = unique (ss, ss+sz) - ss;
		my.init ();
		for (int i=0, x; i<sz; i++) {
			x = my.alloc (ss[i],ss[i]);
			tt[i] = x;
			my.merge (rt, rt, x);
			if (ss[i]+1!=ss[i+1] && i+1!=sz) {
				x = my.alloc (ss[i]+1, ss[i+1]-1);
				my.merge (rt, rt, x);
			}
		}
//////////////////////////////////////////////////////////////////
		printf ("Case %d:\n", cas);
		for (int i=0; i<Q; i++) {
			if (op[i].s[0]=='T') my.Top(get(op[i].x));
			else if (op[i].s[0]=='R') 
				printf ("%d\n",my.Rank(rt,op[i].x));
			else {int o = get(op[i].x);
				printf ("%d\n", my.Query(o)+T[o].sum-T[rs[o]].sum);
			}
		}
	}
	return 0;
}
