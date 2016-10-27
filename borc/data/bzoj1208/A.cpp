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

const int M = 100000, nill = 0, mod = 1000000;
int ls[M], rs[M];
struct Node {
	int sz;
	unsigned fix;
	int v;
	inline void init(int _v) {
		sz=1, fix=rand();
		v=_v;
	}
} T[M];

int MY;
inline int alloc (int _v) {
	T[MY].init(_v); ls[MY]=rs[MY]=nill; return MY++;
}

struct Treap{
	int rt;
	inline void init () {rt=nill;}
	inline void up(int o) {
		T[o].sz=1+T[ls[o]].sz+T[rs[o]].sz;
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
		if (k>T[ls[o]].sz)cut(rs[o],rs[a=o],b,k-T[ls[o]].sz-1);
		else cut(ls[o],a,ls[b=o],k);
		up(o);
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
	int askR (int o,int v,int &dif) {
		if (o==nill) return 0;
		int ret=0;
		if (v>=T[o].v) dif=v-T[o].v;
		if (v==T[o].v) {
			ret=T[ls[o]].sz;
		} else if (v<T[o].v) {
			ret=askR(ls[o],v,dif);
		} else ret=T[ls[o]].sz+1+askR(rs[o],v,dif);
		return ret;
	}
	void ins (int v) {
		int dif=-1;
		int a,b,c, k=askR(rt,v,dif);
		cut (rt, a, b, k);
		merge (rt, a, alloc(v));
		merge (rt, rt, b);
	}
	int upper (int o,int v,int &dif) {
		if (o==nill) return 0;
		int ret=0;
		if (T[o].v>v) {
			dif = T[o].v-v;
			ret = upper (ls[o],v,dif);
		} else ret = 1+T[ls[o]].sz + upper (rs[o],v,dif);
		return ret;
	}
	int ask (int v) {
		int dif1=-1, dif2=-1;
		int a,b,c, k1=askR(rt,v,dif1), k2=upper(rt,v,dif2);
		if (dif1) k1--;
		//printf ("v=%d,dif1=%d,dif2=%d\n",v,dif1,dif2);
		//printf ("k1=%d,k2=%d\n", k1, k2);
		if (dif1==-1) {
			cut (rt, a, b, k2);
			cut (b, b, c, 1);
			merge (rt, a, c);
			return dif2;
		} else if (dif2==-1) {
			cut (rt, a, b, k1);
			cut (b, b, c, 1);
			merge (rt, a, c);
			return dif1;
		} else if (dif1<=dif2) {
			cut (rt, a, b, k1);
			cut (b, b, c, 1);
			merge (rt, a, c);
			return dif1;
		} else {
			cut (rt, a, b, k2);
			cut (b, b, c, 1);
			merge (rt, a, c);
			return dif2;
		}
	}
	inline int size() {return T[rt].sz;}
}my[2];

int Q;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand(233);
	scanf ("%d", &Q);
	MY=1, my[0].init(), my[1].init();
	int a, b;
	int ans=0;
	while (Q --) {
		scanf ("%d%d", &a,&b);
		if (SZ(my[!a])==0) {
			my[a].ins(b);
		} else {
			ans = (ans+my[!a].ask (b))%mod;
		}
	}
	printf ("%d\n", ans);
	return 0;
}
