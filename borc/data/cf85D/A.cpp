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

const int M=100000+10, nill=0;
int ls[M<<1], rs[M<<1], rt;
struct Node {
	ll sum[5], x,v;
	int mk;
	int sz;
	unsigned fix;
	inline void init (int _x,int _v) {
		fix=rand(), sz=1;
		memset (sum, 0, sizeof(sum));
		x=_x, v=_v, sum[_x%5] = _v, mk=0;
	}
	inline void init2 () {
		memset (sum, 0, sizeof(sum));
		sum[x%5] = v;
	}
	inline void mark (int lz) {
		x += lz;
		mk += lz;
		lz %= 5;
		ll tmp[5]; 
		memcpy (tmp,sum,sizeof(sum));
		for (int i=0; i<5; i++) sum[i]=tmp[(i-lz+5)%5];
	}
}T[M<<1];

struct Treap {
	int MY;
	void init () {MY=1;rt=nill;}
	inline int alloc (int id,int v) {
		T[MY].init(id,v); ls[MY]=rs[MY]=0; return MY++;
	}
	inline void down (int o) {
		if (T[o].mk) {
			if (ls[o]!=nill) T[ls[o]].mark(T[o].mk);
			if (rs[o]!=nill) T[rs[o]].mark(T[o].mk);
			T[o].mk=0;
		}
	}
	inline void up (int o) {
		T[o].init2();
		T[o].sz = 1+T[ls[o]].sz+T[rs[o]].sz;
		for (int i=0; i<5; i++) 
			T[o].sum[i]+=T[ls[o]].sum[i]+T[rs[o]].sum[i];
	}
	void cut (int o,int &a,int &b,int k) {
		if(T[o].sz<=k) {a=o,b=nill;return;}
		if(k<=0) {a=nill,b=o;return;}
		down(o);
		if (k>T[ls[o]].sz) cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up(o);
	}
	void merge (int &o,int a,int b) {
		if (a==nill) o=b;
		else if (b==nill) o=a;
		else if (T[a].fix>T[b].fix) {
			down(o=a); merge(rs[o],rs[a],b); up(o);
		} else {
			down(o=b); merge(ls[o],a,ls[b]); up(o);
		}
	}
	int askR (int o,int v) {
		if (o==nill) return 0;
		down (o);
		ll ret=0;
		if (v<=T[o].v) ret += askR(ls[o],v);
		else ret += 1+T[ls[o]].sz+askR(rs[o],v);
		up (o);
		return ret;
	}
	void ins (int v) {
		int a,b,c, k=askR(rt,v);
		//printf ("v=%d,k=%d\n", v,k);
		cut (rt, a, b, k);
		merge (rt, a, alloc(k+1,v));
		//puts ("before down:");
		//for (int i=0; i<5; i++)printf(LLD" ",T[b].sum[i]);puts ("");
		if(b!=nill) T[b].mark(1);
		//puts ("after down:");
		//for (int i=0; i<5; i++)printf(LLD" ",T[b].sum[i]);puts ("");
		merge (rt, rt, b);
	}
	void del (int v) {
		int a,b,c, k=askR(rt,v);
		cut (rt, a, b, k);
		cut (b, b, c, 1);
		//puts ("before down:");
		//for (int i=0; i<5; i++)printf(LLD" ",T[c].sum[i]);puts ("");
		if (c!=nill) T[c].mark(-1);
		//puts ("after down:");
		//for (int i=0; i<5; i++)printf(LLD" ",T[c].sum[i]);puts ("");
		//printf ("a=%d\n", a);
		merge (rt, a, c);
	}
	void Print (int o) {
		if (o==0) return;
		Print (ls[o]); 
		printf ("%d ", T[o].v);
		Print (rs[o]);
	}
}my;

int Q;

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d", &Q);
	my.init();
	while (Q --) {char op[10]; int v;
		//my.Print (rt); puts ("");
		//puts ("rt:");
		//for (int i=0; i<5; i++)printf(LLD" ",T[rt].sum[i]);puts("");puts("");
		scanf ("%s", op);
		if (op[0]=='a') {
			scanf ("%d", &v);
			my.ins (v);
		} else if (op[0]=='d') {
			scanf ("%d", &v);
			my.del(v);
		} else {
			printf (LLD"\n", T[rt].sum[3]);
		}
	}
	return 0;
}
