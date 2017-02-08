#include <stdio.h>
#include <numeric>
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
#include <limits.h>
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
#define SZ(x) ((int)x.size())
#define lson (o<<1),l,mid
#define rson (o<<1|1),mid+1,r
#define MP make_pair
#define sqr(x) ((x)*(x))
#define ALL(v) (v).begin(),(v).end()
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
const double eps = 1e-9 ;
const int MOD=(int)1e9+7,BAS=233;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}
int AP (char *s) {
	unsigned hash=0;
	for(int i=0; s[i]; i++){
		if (i & 1) hash ^= (~((hash<<11)^s[i]^(hash>>5)));
		else hash ^= ((hash<<7)^s[i]^(hash>>3));
   } return hash & 0x7FFFFFFF;
}

const int M = 100000+10;
const ll inf = -1e15;
struct Node {
	ll maxn;//历史最大值
	ll sum;//当前最大值
	ll fmk;//历史mk最大值
	ll mk;
	void mark (ll maxmk,ll v) {
		fmk = max(fmk, mk+maxmk);
		mk += v;
		maxn = max(maxn, sum+maxmk);
		sum += v;
	}
} T[M<<2];
struct Segtree {
	void down (Node &o,Node &ls,Node &rs) {
		if (o.mk==0 && o.fmk==0) return;
		ls.mark(o.fmk,o.mk);
		rs.mark(o.fmk,o.mk);
		o.mk=o.fmk=0;
	}
	Node up (Node ls,Node rs) {
		return Node{max(ls.maxn,rs.maxn), max(ls.sum,rs.sum), 0};
	}
	void update (int o,int l,int r,int pl,int pr,int v) {
		if (pl<=l && r<=pr) {T[o].mark(max(0,v),v); return;}
		down (T[o],T[o<<1],T[o<<1|1]);
		int mid = l+r>>1;
		if (pl<=mid) update(lson,pl,pr,v);
		if (pr>mid) update(rson,pl,pr,v);
		T[o] = up(T[o<<1],T[o<<1|1]);
	}
	Node ask (int o,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[o];
		int mid = l+r>>1;
		down (T[o],T[o<<1],T[o<<1|1]);
		Node ret;
		if (pl<=mid && pr>mid) ret=up(ask(lson,pl,pr),ask(rson,pl,pr));
		else if (pl<=mid) ret=ask(lson,pl,pr);
		else if (pr>mid) ret=ask(rson,pl,pr);
		T[o] = up(T[o<<1],T[o<<1|1]);
		return ret;
	}
} sgt;

struct Query {
	int l, r, id;
	inline bool operator < (const Query &rhs) const {
		return r<rhs.r;
	}
}qu[M];
int n, Q;
int a[M];
ll ans[M];
int pos[M<<1];

inline int getpos (int x) {
	return pos[x+M];
}
inline void up_pos (int x,int v) {
	pos[x+M] = v;
}

int main () {
	scanf ("%d", &n);
	for (int i=1; i<=n; i++) scanf ("%d", a+i);
	scanf ("%d", &Q);
	for (int i=0; i<Q; i++) {
		scanf ("%d%d", &qu[i].l,&qu[i].r);
		qu[i].id=i;
	}
	sort (qu, qu+Q);
	for (int i=1, j=0; i<=n; i++) {
		sgt.update (1,1,n,getpos(a[i])+1,i,a[i]);
		up_pos (a[i],i);
		while (j<Q && qu[j].r==i) {
			ans[qu[j].id] = sgt.ask (1,1,n,qu[j].l,i).maxn;
			j ++;
		}
	}
	for (int i=0; i<Q; i++) {
		printf(LLD"\n", ans[i]);
	}
	return 0;
}
