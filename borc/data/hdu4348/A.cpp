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

const int M = 100000+10;
int ls[M*30], rs[M*30], rt[M];

struct NODE {
	ll sum, add;
	inline void mark (int lz) {
		add += lz;
	}
};

struct PERSIST {
	NODE T[M*30]; 
	int n;
	inline int init () { n=0; return newnode();}
	inline int newnode () { return n++;}
	inline int up (int o) {
		T[o].sum = T[ls[o]].sum + T[rs[o]].sum;
	}
	void build (int o,int l,int r) {
		T[o].add = 0;
		if (l == r) {
			scanf (LLD, &T[o].sum);
			return;
		}
		int mid = l+r>>1;
		build (ls[o]=newnode(),l,mid);
		build (rs[o]=newnode(),mid+1,r);
		up (o);
	}
	void ins (int o,int l,int r,int u,int pl,int pr,int lz) {
		T[u] = T[o];
		T[u].sum += 1ll*lz*(min(r,pr) - max(l,pl)+1);
		ls[u] = ls[o], rs[u] = rs[o];
		if (pl<=l && r<=pr) {T[u].mark (lz); return;}
		int mid = l+r>>1;
		if (pl<=mid) ins (ls[o],l,mid,ls[u]=newnode(),pl,pr,lz);
		if (pr>mid) ins (rs[o],mid+1,r,rs[u]=newnode(),pl,pr,lz);
	}
	ll ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[o].sum;
		ll ret = 1ll*T[o].add*(min(r,pr) - max(l,pl)+1);
		int mid = l+r>>1;
		if (pl<=mid) ret += ask (ls[o],l,mid,pl,pr);
		if (pr>mid) ret += ask (rs[o],mid+1,r,pl,pr);
		return ret;
	}
} sgt;

int n, m;

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n, &m)) {
		sgt.build (rt[0]=sgt.init(), 1, n);
		int tim = 0;
		while (m --) { char op[10]; int l, r, d, t;
			scanf ("%s", op);
			if (op[0] == 'C') {
				scanf ("%d%d%d", &l, &r, &d);
				rt[++tim] = sgt.newnode();
				sgt.ins (rt[tim-1],1,n,rt[tim],l,r,d);
			} else if (op[0] == 'Q') {
				scanf ("%d%d", &l, &r);
				printf (LLD"\n", sgt.ask (rt[tim],1,n,l,r));
			} else if (op[0] == 'H') {
				scanf ("%d%d%d", &l, &r, &t);
				printf (LLD"\n", sgt.ask (rt[t],1,n,l,r));
			} else scanf ("%d", &tim);
		}
	}
	return 0;
}
