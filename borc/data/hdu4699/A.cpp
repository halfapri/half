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

const int M = 1000000+10, nill=0;
int ls[M], rs[M], I, ed, rt;
struct Node {
	int v, sum, maxn;
	int sz;
	unsigned fix;
	inline void init (int _v) {
		v=sum=maxn=_v, sz=1, fix=rand();
	}
} T[M];

struct Treap {
	int MY;
	void init () {MY=1;T[0].init(0),T[0].sz=0;I=0,ed=0;}
	inline int alloc (int v) {
		T[MY].init(v); ls[MY]=rs[MY]=0; return MY++;
	}
	inline void up (int o) {
		T[o].sz = 1+T[ls[o]].sz+T[rs[o]].sz;
		T[o].sum = T[o].v+T[ls[o]].sum+T[rs[o]].sum;
		if (ls[o]==nill) {
			T[o].maxn = max (T[o].v, T[o].v+T[rs[o]].maxn);
		} else {
			T[o].maxn = max(T[ls[o]].maxn, max(T[ls[o]].sum+T[o].v,
						T[ls[o]].sum+T[o].v+T[rs[o]].maxn));
		}
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
	void ins (int v) {
		int o=alloc(v), a,b,c;
		cut (rt, a, b, I);
		merge (rt, a, o);
		merge (rt, rt, b);
		//printf ("rt.maxn=%d\n", T[rt].maxn);
		I ++;
		ed ++;
	}
	void del () {
		if (ed==0 || I==0) return;
		int a,b,c;
		cut (rt, a, b, I-1);
		cut (b, b, c, 1);
		merge (rt, a, c);
		I --;
		ed --;
		if (I>ed) I=ed;
		if (I<0) I=0;
	}
	void moveL () {I --; if(I<0) I=0;}
	void moveR () {I ++; if(I>ed) I=ed;}
	int ask (int k) {
		k = min (k, I);
		int a,b,c;
		cut (rt, a, b, k);
		int ans = T[a].maxn;
		merge (rt, a, b);
		return ans;
	}
} my;

int Q;

int main () {
	srand(time(0));
	while (~ scanf("%d", &Q)) {
		rt = nill;
		my.init();
		char op[10];
		int x, k;
		while (Q --) {
			scanf ("%s", op);
			if (op[0]=='I') {
				scanf ("%d", &x);
				my.ins(x);
			} else if (op[0]=='D') {
				my.del();
			} else if (op[0]=='L') {
				my.moveL();
			} else if (op[0]=='R') {
				my.moveR();
			} else {
				scanf ("%d", &k);
				printf ("%d\n", my.ask(k));
			}
		}
	}
	return 0;
}
