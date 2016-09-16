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

const int M = 400000+10;
int sa[M], rk[M], h[M];

void da (int *s,int n,int m) {
	static int t1[M], t2[M], c[M];
	int *x=t1, *y=t2, i,j,k,p=1;
	memset (c, 0, sizeof(c[0])*m);
	for (i=0; i<n; i++) c[x[i]=s[i]]++;
	for (i=1; i<m; i++) c[i] += c[i-1];
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i;
		for (i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k;
		memset (c, 0, sizeof(c[0])*m);
		for (i=0; i<n; i++) c[x[i]]++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (k=i=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
}
//////////////////////////////////////////////////////////////////

int rt[M], ls[M*11], rs[M*11], T[M*11];
struct PERSIST {
	int sz;
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
	int ask (int o,int u,int l,int r,int pl,int pr) {
		if (pl<=l && r<=pr) return T[u]-T[o];
		int mid = l+r>>1, ret=0;
		if (pl<=mid) ret += ask (ls[o],ls[u],l,mid,pl,pr);
		if (pr>mid) ret += ask (rs[o],rs[u],mid+1,r,pl,pr);
		return ret;
	}
} pst;
//////////////////////////////////////////////////////////////////

char s[M];
int a[M], col[M], sz, n, Q, cap[M];
int l[M>>1], r[M>>1];

int main () {
	//freopen ("read.txt", "r", stdin);
	scanf ("%d%d", &n, &Q);
	int f = 128;
	sz = 0;
	for (int i=0; i<n; i++) {
		scanf ("%s", s);
		cap[sz] = strlen (s);
		for (int j=0; s[j]; j++) {
			col[sz] = i; a[sz++] = s[j];
		}
		col[sz] = i; a[sz++] = f++;
	}
	a[sz] = 0;
	da (a, sz+1, f);
////////////////////////////////////////
	stack<int>q;
	for (int i=1; i<=sz; i++) {
		while (!q.empty() && h[i]<=h[q.top()]) q.pop();
		if (cap[sa[i]]) {
			if (q.empty()) l[col[sa[i]]] = 1;
			else l[col[sa[i]]] = q.top();
			if (cap[sa[i]]!=h[i]) l[col[sa[i]]] = i;
		} q.push (i);
	}
	while (!q.empty()) q.pop();
	h[sz+1] = 0;
	for (int i=sz; i>=1; i--) {
		while (!q.empty() && h[i+1]<=h[q.top()]) q.pop();
		if (cap[sa[i]]) {
			if (q.empty()) r[col[sa[i]]] = sz;
			else r[col[sa[i]]] = q.top()-1;
			if (cap[sa[i]]!=h[i+1]) r[col[sa[i]]] = i;
		} q.push (i+1);
	}
////////////////////////////////////////
	pst.build (rt[0]=pst.init(),0,n-1);
	for (int i=1; i<=sz; i++) {
		rt[i] = rt[i-1];
		if (a[sa[i]]>=128) continue;
		int lst = rt[i];
		rt[i] = pst.alloc (lst);
		pst.ins (lst,0,n-1,rt[i],col[sa[i]]);
	}
	while (Q --) {int pl,pr,x;
		scanf ("%d%d%d", &pl, &pr, &x);pl--,pr--,x--;
		printf ("%d\n", pst.ask(rt[l[x]-1],rt[r[x]],0,n-1,pl,pr));
	}
	return 0;
}
