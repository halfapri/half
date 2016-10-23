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
unsigned fix[M];
int ls[M], rs[M], rt;
int rev[M], w[10], a[M], type;
struct Node {
	int sz;
	unsigned fix;
	int v, num[10];
	bool mk;
	inline void init (int _v) {
		sz=1, fix=rand();
		if (rev[_v]==-1) rev[_v] = type, w[type++] = _v;
		memset (num, 0, sizeof(num)), num[rev[v=_v]]=1, mk=0;
	}
	inline void up (Node &ls,Node &rs) {
		sz=1+ls.sz+rs.sz;
		memset (num,0,sizeof(num)), num[rev[v]]=1;
		for (int i=0; i<10; i++) num[i]+=ls.num[i]+rs.num[i];
	}
	inline void mark (int o) {
		mk^=1, swap(ls[o],rs[o]);
	}
}T[M];

int MY;
inline int alloc(int _v) {
	T[MY].init(_v); ls[MY]=rs[MY]=nill; return MY++;
}

struct Treap {
	inline void up(int o) {T[o].up(T[ls[o]],T[rs[o]]);}
	inline void down(int o) {
		if (T[o].mk) {
			if (ls[o]!=nill) T[ls[o]].mark(ls[o]);
			if (rs[o]!=nill) T[rs[o]].mark(rs[o]);
			T[o].mk=0;
		}
	}
	void build (int &o,int l,int r) {
		if (l>r) return;
		int mid = l+r>>1;
		build (ls[o=alloc(a[mid])],l,mid-1);
		build (rs[o],mid+1,r);
		T[o].fix = fix[mid];
		up(o);
	}
	void cut (int o,int &a,int &b,int k) {
		if (T[o].sz<=k) {a=o,b=nill;return;}
		if (k<=0) {a=nill,b=o;return;}
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
	void update (int id,int v) {
		int a,b,c;
		cut (rt, a, b, id-1);
		cut (b, b, c, 1);
		T[b].num[rev[T[b].v]] --;
		if (rev[v]==-1) rev[v] = type, w[type++]=v;
		T[b].num[rev[T[b].v=v]] ++;
		merge (rt, a, b);
		merge (rt, rt, c);
	}
	void flip (int l,int r) {
		int a,b,c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		T[b].mark(b);
		merge (rt, a, b);
		merge (rt, rt, c);
	}
	void ask (int l,int r,int W) {
		int a,b,c;
		cut (rt, a, b, l-1);
		cut (b, b, c, r-l+1);
		bitset<M> dp(1);
		bool flag=0;
		for (int i=0; i<10 && !flag; i++) {
			int x = T[b].num[i];
			for (int j=1; j<=x && !flag; j<<=1) {
				dp |= dp<<(j*w[i]);
				x -= j;
				if (dp.test(W)) flag=1;
			}
			if (x>0) dp |= dp<<(x*w[i]);
			if (dp.test(W)) flag=1;
		}
		puts (flag ? "Yes" : "No");
		merge (rt, a, b);
		merge (rt, rt, c);
	}
}my;

int n, Q;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand(time(0));
	memset (rev, -1, sizeof(rev));
	for (int i=0; i<M; i++) fix[i]=rand();
	sort (fix, fix+M, [](unsigned a,unsigned b) {
			return a>b;
			});
	scanf ("%d%d", &n, &Q);
	for (int i=1; i<=n; i++) scanf("%d", a+i);
	MY=1;
	my.build (rt,1,n);
	int op, l, r, W, id, x;
	while (Q --) {
		scanf ("%d", &op);
		if (op==1) {
			scanf ("%d%d", &id,&x);
			my.update (id,x);
		} else if (op==2) {
			scanf ("%d%d", &l,&r);
			my.flip (l,r);
		} else {
			scanf ("%d%d%d", &l,&r,&W);
			my.ask(l,r,W);
		}
	}
	return 0;
}
