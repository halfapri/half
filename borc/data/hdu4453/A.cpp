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
int n, m, k1, k2, A[M];
int ls[M], rs[M], rt;
struct NODE {
	int v, sz, add;
	bool mk;
	unsigned fix;
	inline void mark (int op,int lz) {
		if (op==0) mk^=1, swap(ls[lz],rs[lz]);
		else v += lz, add += lz;
	}
} T[M];

struct TREAP {
	int sz, a, b, c;
	void init() {
		T[0].v=T[0].sz=T[0].add=T[0].mk=0,T[0].fix=rand();
		ls[0]=rs[0]=0;sz=1;rt=nill;
	}
	inline int alloc (int v) {
		T[sz].v=v;T[sz].sz=1;T[sz].add=T[sz].mk=0;
		ls[sz]=rs[sz]=nill;T[sz].fix=rand();
		return sz++;
	}
	inline void up (int o) {
		T[o].sz += T[ls[o]].sz + T[rs[o]].sz;
	}
	inline void down (int o) {
		if (T[o].mk) {
			if (ls[o]!=nill) T[ls[o]].mark(0,ls[o]);
			if (rs[o]!=nill) T[rs[o]].mark(0,rs[o]);
			T[o].mk = 0;
		}
		if (T[o].add) {
			if (ls[o]!=nill) T[ls[o]].mark(1,T[o].add);
			if (rs[o]!=nill) T[rs[o]].mark(1,T[o].add);
			T[o].add=0;
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
		else if (T[a].fix > T[b].fix) {
			down (o=a); merge (rs[o],rs[a],b); up (o);
		} else {
			down (o=b); merge (ls[o],a,ls[b]); up (o);
		}
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		o = alloc(A[mid]);
		if (l==r) return;
		build (ls[o],l,mid-1); 
		build (rs[o],mid+1,r);
		up (o);
		T[o].fix = max(T[ls[o]].fix, T[rs[o]].fix);
	}
	void Add (int pos,int lz) {
		if (pos+k2<=n) {
			cut (rt, a, b, pos);
			cut (b, b, c, k2);
			T[b].mark (1, lz);
			merge (rt, a, b);
			merge (rt, rt, c);
		} else {
			cut (rt, a, b, k2-(n-pos));
			cut (b, b, c, n-k2);
			T[a].mark (1, lz);
			T[c].mark (1, lz);
			merge (rt, a, b);
			merge (rt, rt, c);
		}
	}
	void Rev (int pos) {
		if (pos+k1<=n) {
			cut (rt, a, b, pos);
			cut (b, b, c, k1);
			T[b].mark (0, b);
			merge (rt, a, b);
			merge (rt, rt, c);
		} else {
			cut (rt, a, b, k1-(n-pos));
			cut (b, b, c, n-k1);
			merge (a, c, a);
			T[a].mark (0, a);
			cut (a, c, a, n-pos);
			merge (rt, a, b);
			merge (rt, rt, c);
		}
	}
	void Ins (int pos,int v) {
		cut (rt, a, b, pos+1);
		c = alloc (v);
		merge (rt, a, c);
		merge (rt, rt, b);
		n ++;
	}
	void Del (int &pos) {
		cut (rt, a, b, pos);
		cut (b, b, c, 1);
		merge (rt, a, c);
		n --;
		if (pos>=n) pos -= n;
	}
	void Move (int &pos,int x) {
		pos += x;
		if (pos<0) pos += n;
		if (pos>=n) pos -= n;
	}
	void Query (int pos) {
		cut (rt, a, b, pos);
		cut (b, b, c, 1);
		printf ("%d\n", T[b].v);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
} my;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand (time(0));
	int cas=1;
	while (~scanf("%d%d%d%d",&n,&m,&k1,&k2)&& n+m+k1+k2) {
		for (int i=1; i<=n; i++) scanf ("%d", A+i);
		my.init();
		my.build(rt,1,n);
		int pos=0;
		printf ("Case #%d:\n", cas++);
		while (m --) {char s[10];int x;
			scanf ("%s", s);
			if (s[0]=='a') {
				scanf ("%d", &x);
				my.Add (pos,x);
			} else if (s[0]=='r') my.Rev (pos);
			else if (s[0]=='i') {
				scanf ("%d", &x);
				my.Ins (pos, x);
			} else if  (s[0]=='d') my.Del (pos);
			else if (s[0]=='m') {
				scanf ("%d", &x);
				my.Move (pos,x==1?-1:1);
			} else my.Query (pos);
		}
	}
	return 0;
}
