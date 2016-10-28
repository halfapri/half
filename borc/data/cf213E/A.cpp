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
template <class T> inline int SZ(T x){return (int)x.size();}

const int M = 200000, nill=0;
int ls[M], rs[M];
ll pw[M], sumpw;
struct Node {
	int sz;
	unsigned fix;
	int x,v;
	ll hs;
	void init (int _x,int _v) {
		sz=1, fix=rand();
		x=_x,v=_v,hs=_v;
	}
}T[M];

int MY;
inline int alloc (int _x,int _v) {
	T[MY].init(_x,_v); ls[MY]=rs[MY]=nill; return MY++;
}

struct Treap {
	int rt;
	void init () {rt=nill;}
	inline void up (int o) {
		T[o].sz = 1+T[ls[o]].sz+T[rs[o]].sz;
		T[o].hs = T[o].v;
		if (ls[o]!=nill) {
			T[o].hs=(T[ls[o]].hs+pw[T[ls[o]].sz]*T[o].v)%MOD;
		}
		if (rs[o]!=nill) {
			T[o].hs=(T[o].hs+pw[T[ls[o]].sz+1]*T[rs[o]].hs)%MOD;
		}
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
		if (k>T[ls[o]].sz) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up(o);
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			merge (rs[o=a],rs[a],b); up(o);
		} else {
			merge (ls[o=b],a,ls[b]); up(o);
		}
	}
	int askR (int o,int x) {
		if (o==nill) return 0;
		int ret=0;
		if (x<=T[o].x) ret=askR(ls[o],x);
		else ret=1+T[ls[o]].sz+askR(rs[o],x);
		return ret;
	}
	void ins (int x,int v) {
		int a,b,c, k=askR(rt,x);
		cut (rt, a, b, k);
		merge (rt, a, alloc(x,v));
		merge (rt, rt, b);
		//cout << "x=" << x << ",v=" << v << endl;
		//cout << "rt.sz=" << T[rt].sz << endl;
		//cout << "rt.hs=" << T[rt].hs << endl;
	}
	void del (int x) {
		int a,b,c, k=askR(rt,x);
		cut (rt, a, b, k);
		cut (b, b, c, 1);
		merge (rt, a, c);
	}
	inline ll ask (int x) {
		return ((T[rt].hs-x*sumpw)%MOD+MOD)%MOD;
	}
}my;

int b[M], posb[M], n, m;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand (time(0));
	sumpw=pw[0]=1;
	scanf ("%d%d", &n,&m);
	for (int i=1; i<=m; i++) {
		pw[i] = pw[i-1]*BAS%MOD;
		if (i<n) sumpw = (sumpw+pw[i])%MOD;
	}
	ll key=0;
	for (int i=0,a; i<n; i++) {
		scanf ("%d", &a);
		key = (key+a*pw[i])%MOD;
	}
	for (int i=0; i<m; i++) {
		scanf("%d", b+i);
		posb[b[i]]=i;
	}
	MY=1, my.init();
	for (int i=1; i<n; i++) my.ins (posb[i],i);
	int ans = 0;
	for (int i=n; i<=m; i++) {
		my.ins (posb[i],i);
		//cout << "my=" << my.ask(i-n) << endl;
		if (my.ask(i-n) == key) ans++;
		my.del (posb[i-n+1]);
	}
	printf ("%d\n", ans);
	return 0;
}
