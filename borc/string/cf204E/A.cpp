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
const int MOD=(int)1e9+21,BAS=257;
inline int sign(double x){return x<-eps?-1:x>eps;}
inline int clz(int x){return __builtin_clz(x);}
inline int clz(ll x){return __builtin_clzll(x);}
inline int lg2(int x){return !x ? -1 : 31-clz(x);}
inline int lg2(ll x){return !x ? -1 : 63-clz(x);}

const int M = 200000+10;
int sa[M], rk[M], h[M];

void da (int *s,int n,int m) {
	static int t1[M], t2[M], c[M];
	int *x=t1, *y=t2, i,j,k,p=1;
	memset (c, 0, sizeof(c[0])*m);
	for (int i=0; i<n; i++) c[x[i] = s[i]]++;
	for (int i=1; i<m; i++) c[i] += c[i-1];
	for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i;
		for (i=0; i<n; i++) if(sa[i]>=k) y[p++] = sa[i]-k;
		memset (c, 0, sizeof(c[0])*m);
		for (i=0; i<n; i++) c[x[i]] ++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (k=0, i=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
}

//////////////////////////////////////////////////////////////////
int rt[M], ls[M*22], rs[M*22];
struct PERSIST {
	int T[M*22], sz;
	int init () {sz=0;return sz++;}
	inline int alloc (int o) {
		ls[sz] = ls[o], rs[sz] = rs[o], T[sz] = T[o]; return sz++;
	}
	void build (int o,int l,int r) {
		T[o] = 0;
		if (l == r) return;
		int mid = l+r>>1;
		build (ls[o]=sz++,l,mid);
		build (rs[o]=sz++,mid+1,r);
	}
	void ins (int o,int l,int r,int u,int x) {
		if (l == r) {T[u]++;return;}
		int mid = l+r>>1;
		if (x<=mid) ins (ls[o],l,mid,ls[u]=alloc(ls[o]),x);
		else ins (rs[o],mid+1,r,rs[u]=alloc(rs[o]),x);
		T[u] = T[ls[u]] + T[rs[u]];
	}
	int ask (int o,int l,int r,int pr) {
		if (r<=pr) return T[o];
		int mid = l+r>>1, ret=0;
		ret += ask (ls[o],l,mid,pr);
		if (pr>mid) ret += ask (rs[o],mid+1,r,pr);
		return ret;
	}
} pst;

//////////////////////////////////////////////////////////////////
struct SEGTREE {
	int T[M<<2];
	void build (int o,int l,int r) {
		if (l == r) {T[o]=h[l];return;}
		int mid = l+r>>1;
		build (lson); build (rson);
		T[o] = min (T[o<<1], T[o<<1|1]);
	}
	int askl (int o,int l,int r,int x,int v) {
		if (v<=T[o]) return -1;
		if (l == r) return l;
		int mid = l+r>>1, ret=-1;
		if (x>mid) ret = askl (rson,x,v);
		if (~ret) return ret;
		return askl (lson,x,v);
	}
	int askr (int o,int l,int r,int x,int v) {
		if (v<=T[o]) return -1;
		if (l == r) return l;
		int mid = l+r>>1, ret=-1;
		if (x<=mid) ret = askr (lson,x,v);
		if (~ret) return ret;
		return askr (rson,x,v);
	}
} sgt;

//////////////////////////////////////////////////////////////////
int n, k, col[M], a[M], sz, vmax[M], cap[M];
ll ans[M];
char s[M];

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%d%d", &n,&k)) {
		sz=0;
		int f=128;
		for (int i=0; i<n; i++) {
			scanf ("%s", s);
			int len = strlen (s);
			for (int j=0; s[j]; j++) {
				cap[sz] = len-j;
				col[sz] = i;
				a[sz++] = s[j];
			}
			col[sz] = i;
			a[sz++] = f++;
		}
		a[sz] = 0;
		da (a, sz+1, f);  
//////////////////////////////////////////////////////////////////
		memset (vmax, 0, sizeof(vmax[0])*(sz+1));
		pst.build (rt[0]=pst.init(),0,sz);
		for (int i=1; i<=sz; i++) {
			rt[i] = pst.alloc (rt[i-1]);
			pst.ins (rt[i-1],0,sz,rt[i],vmax[col[sa[i]]]);
			vmax[col[sa[i]]] = i;
		}
//////////////////////////////////////////////////////////////////
		sgt.build (1,1,sz);
		h[sz+1] = 0;
		//for (int i=1; i<=sz; i++) printf("%d ",h[i]);puts("");
		for (int i=1; i<=sz; i++) if (a[sa[i]]<128){
			int l=1, r=cap[sa[i]], ret=0, mid, pl, pr, judge;
			while (l<=r) {
				mid = l+r>>1;
				pl = sgt.askl (1,1,sz,i,mid);
				if (pl==-1) pl = 1; 
				pr = i==sz ? sz : sgt.askr (1,1,sz,i+1,mid)-1;
				//printf ("length=%d,pl=%d,pr=%d\n",mid,pl,pr);
				if (pr<0) pr = sz;
				judge = pst.ask(rt[pr],0,sz,pl-1) -
					pst.ask(rt[pl-1],0,sz,pl-1);
				if (judge>=k) ret=mid, l=mid+1;
				else r=mid-1;
			}
			//printf ("sa[%d]=%d,ret=%d\n", i,sa[i],ret);
			ans[col[sa[i]]] += ret;
		}
		for (int i=0; i<n; i++) printf (LLD" ", ans[i]);puts("");
	}
	return 0;
}
