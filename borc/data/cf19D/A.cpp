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

const int M = 200000+10, nill=0;
int ls[M], rs[M];
struct Node {
	int sz;
	unsigned fix;
	int x,y;
	int maxy;
	inline void init (int _x,int _y) {
		sz=1, fix=rand();
		x=_x,y=maxy=_y;
	}
}T[M];

int MY;
inline int alloc (int _x,int _y) {
	T[MY].init(_x,_y); ls[MY]=rs[MY]=nill; return MY++;
}

struct Treap {
	int rt;
	void init () {rt=0;}
	inline int size() {return T[rt].sz;}
	inline void up (int o) {
		T[o].sz = 1+T[ls[o]].sz+T[rs[o]].sz;
		T[o].maxy = T[o].y;
		if (ls[o]!=nill) T[o].maxy=max(T[o].maxy,T[ls[o]].maxy);
		if (rs[o]!=nill) T[o].maxy=max(T[o].maxy,T[rs[o]].maxy);
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
	inline bool better (Node &f,int &x,int &y) {
		if (x==f.x) return y<=f.y;
		return x<f.x;
	}
	int askR (int o,int x,int y) {
		if (o==nill) return 0;
		int ret=0;
		if (better(T[o],x,y)) ret=askR(ls[o],x,y);
		else ret=1+T[ls[o]].sz+ askR(rs[o],x,y);
		return ret;
	}
	void ins (int x,int y) {
		int a,b, k=askR(rt,x,y);
		cut (rt, a, b, k);
		merge (rt, a, alloc(x,y));
		merge (rt, rt, b);
	}
	void del (int x,int y) {
		int a,b,c, k=askR(rt,x,y);
		cut (rt, a, b, k);
		cut (b, b, c, 1);
		merge (rt, a, c);
	}
	int askR (int o,int x) {
		if (o==nill) return 0;
		int ret=0;
		if (x<T[o].x) ret=askR(ls[o],x);
		else ret=1+T[ls[o]].sz+askR(rs[o],x);
		return ret;
	}
	void bins (int o,int y,int &ansx,int &ansy) {
		if (o==nill || T[o].maxy<=y) return;
		if (ansx==-1 && T[o].y>y) ansx=T[o].x, ansy=T[o].y;
		else if (T[o].x<ansx && T[o].y>y) ansx=T[o].x, ansy=T[o].y;
		else if (T[o].x==ansx && T[o].y>y && T[o].y<ansy) ansy=T[o].y;
		//printf ("(%d,%d):ls.maxy=%d,rs.maxy=%d\n", T[o].x,T[o].y,T[ls[o]].maxy,T[rs[o]].maxy);
		//printf ("ls.x=%d,rs.x=%d\n", T[ls[o]].x,T[rs[o]].x);
		if (T[ls[o]].maxy>y) bins (ls[o],y,ansx,ansy);
		else if (T[rs[o]].maxy>y) bins (rs[o],y,ansx,ansy);
	}
	void ask (int x,int y) {
		int a,b,c, k=askR(rt,x);
		if (k==size()) {puts ("-1"); return;}
		cut (rt, a, b, k);
		int ansx=-1, ansy=-1;
		bins (b,y,ansx,ansy);
		merge (rt, a, b);
		if (ansx==-1) {puts ("-1"); return;}
		printf ("%d %d\n", ansx,ansy);
	}
}my;

int Q;

int main () {
	//freopen ("read.txt", "r", stdin);
	srand(time(0));
	MY=1, my.init();
	scanf ("%d", &Q);
	char op[10];
	int x,y;
	while (Q --) {
		scanf("%s", op);
		if (op[0]=='a') {
			scanf ("%d%d", &x,&y);
			my.ins(x,y);
		} else if (op[0]=='f') {
			scanf ("%d%d", &x,&y);
			my.ask(x,y);
		} else {
			scanf ("%d%d", &x,&y);
			my.del(x,y);
		}
	}
	return 0;
}
