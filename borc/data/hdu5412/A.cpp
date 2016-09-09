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
int ls[M*40], rs[M*40], rt[M], S[M], xx[M], yy[M];
int ss[M<<1], sz;
int n, m, a[M];

struct PERSIST {
	int T[M*40], n;
	int init () {n=0; return newnode();}
	inline int newnode () {return n++;}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=newnode(),l,mid);
		build (rs[o]=newnode(),mid+1,r);
	}
	void ins (int x,int k,int val) {
		for (; x<=n; x+=x&-x) {
			int lst = S[x];
			ins (lst, 0, sz-1, S[x]=newnode(), k, val);
		}
	}
	void ins (int o,int l,int r,int u,int x,int val) {
		T[u] = T[o] + val;
		ls[u] = ls[o], rs[u] = rs[o];
		if (l == r) return;
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=newnode(),x,val);
		else ins (rs[o],mid+1,r,rs[u]=newnode(),x,val);
	}
	int ask (int x,int *xx,int *son,int ret=0) {
		for (; x; x-=x&-x) ret += T[son[xx[x]]];
		return ret;
	}
	int ask (int x,int y,int u,int v,int l,int r,int k) {
		if (l == r) return l;
		int mid = l+r>>1;
		int sum = T[ls[v]]-T[ls[u]]+ask(y,yy,ls)-ask(x,xx,ls);
		if (k <= sum) {
			for (int i=x; i; i-=i&-i) xx[i] = ls[xx[i]];
			for (int i=y; i; i-=i&-i) yy[i] = ls[yy[i]];
			return ask (x,y,ls[u],ls[v],l,mid,k);
		} 
		for (int i=x; i; i-=i&-i) xx[i] = rs[xx[i]];
		for (int i=y; i; i-=i&-i) yy[i] = rs[yy[i]];
		return ask (x,y,rs[u],rs[v],mid+1,r,k-sum);
	}
} sgt;

struct OP {
	int op, l, r, k, v;
} op[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d", &n)) {
		sz=0;
		for (int i=1; i<=n; i++) scanf ("%d", a+i), ss[sz++]=a[i];
		scanf ("%d", &m);
		for (int i=1; i<=m; i++) {
			scanf ("%d", &op[i].op);
			if (op[i].op==1) {
				scanf ("%d%d", &op[i].l,&op[i].v);
				ss[sz++] = op[i].v;
			} else scanf ("%d%d%d", &op[i].l,&op[i].r,&op[i].k);
		}
		sort (ss, ss+sz);
		sz = unique (ss, ss+sz) - ss;
//////////////////////////////////////////////////////////////////
		auto get = [&] (int x) {
			return lower_bound (ss, ss+sz, x) - ss;
		};
//////////////////////////////
		sgt.build (rt[0]=sgt.init(),0,sz-1);
		for (int i=1; i<=n; i++) {
			rt[i] = sgt.newnode();
			sgt.ins (rt[i-1],0,sz-1,rt[i],get(a[i]),1);
		}
		memset (S, 0, sizeof(S[0])*(n+1));
		for (int i=1; i<=m; i++) {
			if (op[i].op==1) {
				sgt.ins (op[i].l,get(a[op[i].l]),-1);
				sgt.ins (op[i].l,get(op[i].v),1);
				a[op[i].l] = op[i].v;
			} else {int l=op[i].l-1, r=op[i].r, k=op[i].k;
				for (int x=l; x; x-=x&-x) xx[x] = S[x];
				for (int x=r; x; x-=x&-x) yy[x] = S[x];
				int x = sgt.ask (l,r,rt[l],rt[r],0,sz-1,k);
				printf ("%d\n", ss[x]);
			}
		}
	}
	return 0;
}
