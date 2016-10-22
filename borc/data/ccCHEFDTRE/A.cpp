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

const int M = 100000+10,nill=0;
int ls[M], rs[M];
struct Node {
	int sz;
	unsigned fix;
	int v;
	inline void init (int _v) {
		sz=1, fix=rand();
		v=_v;
	}
	inline void up (Node &ls,Node &rs) {
		sz=1+ls.sz+rs.sz;
	}
}T[M];

int MY=1;
int alloc (int _v) {
	T[MY].init(_v); ls[MY]=rs[MY]=nill; return MY++;
}

struct Treap {
	int rt;
	void init (int _v) {rt=alloc(_v);}
	inline int alloc(int _v) {
		T[MY].init(_v); ls[MY]=rs[MY]=nill; return MY++;
	}
	inline void up(int o) {T[o].up(T[ls[o]],T[rs[o]]);}
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
			merge(rs[o=a],rs[a],b); up(o);
		} else {
			merge(ls[o=b],a,ls[b]); up(o);
		}
	}
	int askR (int o,int v) {
		if (o==nill) return 0;
		int ret=0;
		if (v<=T[o].v) ret+=askR(ls[o],v);
		else ret+=1+T[ls[o]].sz+askR(rs[o],v);
		return ret;
	}
	void ins (int o) {
		ls[o]=rs[o]=nill, T[o].sz=1;
		int a,b,c, k=askR(rt,T[o].v);
		cut (rt, a, b, k);
		merge (rt, a, o);
		merge (rt, rt, b);
	}
	int ask (int k) {
		int a,b,c;
		cut (rt, a, b, k-1);
		cut (b, b, c, 1);
		int ans = T[b].v;
		merge (rt, a, b);
		merge (rt, rt, c);
		return ans;
	}
	inline int getsz() {return T[rt].sz;}
}my[M*3];

int n, Q;

void dfs (int o,Treap &a) {
	if (o==nill) return;
	dfs (ls[o], a);
	dfs (rs[o], a);
	a.ins (o);
}

void Union (Treap &a,Treap &b) {
	if (a.getsz()<b.getsz()) swap(a.rt,b.rt);
	dfs (b.rt,a);
	my[++n].rt = a.rt;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d%d", &n, &Q);
	for (int i=1; i<=n; i++) my[i].init(i);
	char op[10];
	int a,b;
	while (Q--) {
		scanf ("%s%d%d", op,&a,&b);
		if (op[0]=='U') {
			Union (my[a],my[b]);
		} else {
			printf ("%d\n", my[a].ask(b));
		}
	}
	return 0;
}
