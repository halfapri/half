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

const int M = 270000, nill=0;
int ls[M], rs[M], rt;
struct Node {
	int v,sz;
	unsigned fix;
} T[M];

struct Treap {
	int MY, a, b, c;
	inline void init () {
		T[0].v=T[0].sz=ls[0]=rs[0]=rt=0, MY=1;
	}
	inline int alloc (int v) {
		T[MY].v=v, T[MY].sz=1;
		ls[MY]=rs[MY]=nill; return MY++;
	}
	inline void down (int o) {
		T[o].sz=1;
	}
	inline void up (int o) {
		T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k==0) {b=o,a=nill;return;}
		down (o);
		if (T[ls[o]].sz<k) cut(rs[o],rs[a=o],b,k-1-T[ls[o]].sz);
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
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		o=alloc(mid);
		if (l==r) {T[o].fix=rand();return;}
		build (ls[o],l,mid-1);
		build (rs[o],mid+1,r);
		up (o);
		T[o].fix = max (T[ls[o]].fix, T[rs[o]].fix);
	}
	ll ask (int k) {
		cut (rt, a, b, k-1);
		cut (b, b, c, 1);
		ll ans = T[b].v;
		merge (rt, a, c);
		return ans;
	}
} my;

int n, k;

int main () {
	srand (time(0));
	int CASE, cas=1;
	scanf ("%d", &CASE);
	while (CASE --) {
		scanf ("%d%d", &n,&k);
		my.init();
		my.build (rt,1,n);
		ll ans=0;
		for (int i=0, x; i<k; i++) {
			scanf ("%d", &x);
			ans += my.ask (x);
		}
		printf ("Case %d: "LLD"\n", cas++, ans);
	}
	return 0;
}
