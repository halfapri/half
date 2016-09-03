#include <stdio.h>
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
const int MOD=(int)1e9+7,BAS=257,invBAS=70038911;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 20000+10;
int ls[3000000], rs[3000000], rt[M];

struct PERSIST {
	int T[3000000], n;
	int init () { n=0; return newnode();}
	inline int newnode () { return n++;}
	void build (int o,int l,int r) {
		if (l == r) { T[o] = l; return;}
		int mid = l+r>>1;
		build (ls[o]=newnode(),l,mid);
		build (rs[o]=newnode(),mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x,int fx) {
		ls[u] = ls[o], rs[u] = rs[o];
		if (l == r) {T[u] = fx; return;}
		int mid = l+r>>1;
		if (x<=mid) ins(ls[o],l,mid,ls[u]=newnode(),x,fx);
		else ins(rs[o],mid+1,r,rs[u]=newnode(),x,fx);
	}
	int ask (int o,int l,int r,int x) {
		if (l == r) return T[o];
		int mid = l+r>>1;
		if (x<=mid) return ask (ls[o],l,mid,x);
		else return ask (rs[o],mid+1,r,x);
	}
} sgt;

int n, m;

int dsu (int x,int &o,int &u) {
	int fx = sgt.ask (o,1,n,x);
	if (fx == x) return x;
	fx = dsu (fx, o, u);
	u = sgt.newnode();
	sgt.ins (o,1,n,u,x,fx);
	o = u;
	return fx;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n, &m)) {
		sgt.build (rt[0]=sgt.init(),1,n);
		int tim=0;
		while (m --) {int op, a, b, lst;
			scanf ("%d", &op);
			++tim;
			if (op != 2) {
				scanf ("%d%d", &a, &b);
				a = dsu (a, rt[tim-1], rt[tim]);
				b = dsu (b, rt[tim-1], rt[tim]);
				rt[tim] = rt[tim-1];
				if (op == 3) printf ("%d\n", a == b);
				else if (a!=b) {
					rt[tim] = sgt.newnode();
					sgt.ins (rt[tim-1],1,n,rt[tim],a,b);
				}
			} else {
				scanf ("%d", &lst);
				rt[tim] = rt[lst];
			}
		}
	}
	return 0;
}
