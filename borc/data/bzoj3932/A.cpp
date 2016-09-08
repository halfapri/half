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

const int M = 200000+10;
int ls[M*23], rs[M*23], rt[M];
struct NODE {
	int cnt; 
	ll sum;
}T[M*23];

struct PERSIST {
	int sz;
	int init () {sz=0;return sz++;}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o];
		return sz ++;
	}
	void build (int o,int l,int r) {
		T[o].cnt = T[o].sum = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x,int val) {
		if (l == r) {
			if (val<0) T[u].cnt --; else T[u].cnt ++;
			T[u].sum += val;
			return;
		}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x,val);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x,val);
		T[u].sum = T[ls[u]].sum + T[rs[u]].sum;
		T[u].cnt = T[ls[u]].cnt + T[rs[u]].cnt;
	}
	ll ask (int o,int l,int r,int &k) {
		if (k>T[o].cnt) {k-=T[o].cnt; return T[o].sum;}
		if (l == r) {
			int tmp = k; k=0; 
			return T[o].sum/T[o].cnt*tmp;
		}
		int mid = l+r>>1;
		ll ret = ask (ls[o],l,mid,k);
		if (!k) return ret;
		return ret + ask (rs[o],mid+1,r,k);
	}
}sgt;

int ss[M], sz, n, m, sza;
pair<int,int> a[M];

int get (int x) {
	return lower_bound (ss, ss+sz, x) - ss;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d%d", &n, &m);
	sz = 0;
	ss[sz++] = -inf;
	for (int i=0,j=0,s,e,p; i<n; i++) {
		scanf ("%d%d%d", &s, &e, &p);
		ss[sz++] = p;
		a[j++] = MP(s,p);
		a[j++] = MP(e+1,-p);
	}
	sza = n*2;
	sort (ss, ss+sz);
	sz = unique (ss, ss+sz) - ss;
	sort (a, a+sza);
	sgt.build (rt[0]=sgt.init(),0,sz-1);
	for (int t=1, i=0; t<=n; t++) {
		rt[t] = rt[t-1];
		while (i<sza && t == a[i].fi) {
			int lst = rt[t];
			rt[t] = sgt.alloc(lst);
			sgt.ins (lst,0,sz-1,rt[t],get(abs(a[i].se)),a[i].se);
			i ++;
		}
	}
//////////////////////////////////////////////////////////////////
	ll pre=1;	
	while (m --) {int x,a,b,c;
		scanf ("%d%d%d%d", &x, &a, &b, &c);
		int k = 1 + (a*pre+b)%c;
		pre = sgt.ask (rt[x],0,sz-1,k);
		printf (LLD"\n", pre);
	}
	return 0;
}
