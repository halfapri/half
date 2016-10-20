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
pair<int,int> a[M];
ll pos[M];
int n, Q;
unsigned fix[M];
int ls[M<<1], rs[M<<1], rt;
struct Node {
	ll l, r, x, sum, lxx, rxx;
	int sz;
	unsigned fix;
	inline void init (int _x) {
		l=r=x=_x, sum=lxx=rxx=0, sz=1, fix=rand();
	}
	inline void init2 (int _x) {
		l=r=x=_x, sum=lxx=rxx=0, sz=1;
	}
	inline Node merge (Node &f,int _x,unsigned _fix) {
		Node ret;
		ret.l=l,ret.r=f.r,ret.x=_x,ret.fix=_fix,ret.sz=sz+f.sz;
		ret.sum=sum+f.sum+rxx*f.sz+f.lxx*sz+(f.l-r)*sz*f.sz;
		ret.lxx=lxx+(r-l)*f.sz + f.lxx + (f.l-r)*f.sz;
		ret.rxx=rxx + f.rxx+(f.r-f.l)*sz + (f.l-r)*sz;
		return ret;
	}
}T[M<<1];

struct Treap {
	int MY;
	void init () {MY=1;T[0].init(0),T[0].sz=0;}
	inline int alloc (int _x) {
		T[MY].init(_x); ls[MY]=rs[MY]=nill; return MY++;
	}
	inline void up (int o) {
		T[o].init2 (T[o].x);
		if (ls[o]!=nill)T[o]=T[ls[o]].merge(T[o],T[o].x,T[o].fix);
		if (rs[o]!=nill)T[o]=T[o].merge(T[rs[o]],T[o].x,T[o].fix);
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
		if (k>T[ls[o]].sz) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up (o);
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			merge(rs[o=a],rs[a],b); up(o);
		} else {
			merge(ls[o=b],a,ls[b]); up(o);
		}
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		build (ls[o=alloc(a[mid].fi)],l,mid-1);
		build (rs[o],mid+1,r);
		T[o].fix = fix[mid];
		up (o);
	}
	int askR (int o,int x) {
		if (o==nill) return 0;
		if (x<=T[o].x) return askR(ls[o],x);
		return T[ls[o]].sz+1 + askR(rs[o],x);
	}
	void ins (ll _x,ll x) {
		int a,b,c,k=askR(rt, _x);
		cut (rt, a, b, k);
		cut (b, b, c, 1);
		merge (rt, a, c);
		//puts ("del:"); Print (rt); puts ("");
		k=askR(rt, x);
		cut (rt, a, b, k);
		merge (rt, a, alloc(x));
		merge (rt, rt, b);
	}
	ll ask (int l,int r) {
		int pl = askR(rt, l), pr = askR(rt, r+1),a,b,c;
		//printf ("pl=%d,pr=%d\n", pl, pr);
		cut (rt, a, b, pl);
		cut (b, b, c, pr-pl);
		//printf ("b.sz=%d\n", T[b].sz);
		//puts ("ask:"); Print(b); puts ("");
		ll ans = T[b].sum;
		merge (rt, a, b);
		merge (rt, rt, c);
		return ans;
	}
	void Print (int o) {
		if (o==nill) return;
		Print (ls[o]);
		printf ("%d ", T[o].x);
		Print (rs[o]);
	}
}my;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand(time(0));
	for (int i=0; i<M; i++) fix[i]=rand();
	scanf ("%d", &n);
	for (int i=0; i<n; i++) {
		scanf(LLD, &pos[i]);
		a[i] = MP(pos[i],i+1);
	}
	sort (a, a+n);
	my.init();
	my.build (rt, 0, n-1);
	scanf ("%d", &Q);
	while (Q --) {int op, p, d, l, r;
		//my.Print (rt); puts ("");
		scanf ("%d", &op);
		if (op==1) {
			scanf ("%d%d", &p,&d);
			my.ins (pos[p-1],pos[p-1]+d);
			pos[p-1] += d;
		} else {
			scanf ("%d%d", &l,&r);
			printf (LLD"\n", my.ask (l,r));
		}
	}
	return 0;
}
