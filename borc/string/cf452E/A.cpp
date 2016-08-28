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

const int M = 300000+10, mod = (int)1e9+7;
int rk[M], sa[M], h[M];

void da (char *s,int n,int m) {
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
		for (swap(x,y), x[sa[0]]=0, i=p=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (i=0, k=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
}

char s[M];
int col[M], f0[M], f1[M], f2[M], fa[M], len[4];
int p[M], ans[M];

int dsu (int x) {
	return fa[x]==x? x : fa[x] = dsu(fa[x]);
}

int main () {
	//freopen ("read.txt", "r", stdin);
	len[0] = -1;
	for (int i=1; i<=3; i++) {
		scanf ("%s", s+len[i-1]+1);
		len[i] = strlen (s+len[i-1]+1) + len[i-1]+1;
		s[len[i]] = 122+i;
		for (int j=len[i-1]+1; j<=len[i]; j++) col[j] = i;
	}
	s[len[3]] = 0;
	da (s, len[3]+1, 128);
	for (int i=0; i<=len[3]; i++) {
		p[i] = i;
		fa[i] = i;
		f0[i] = f1[i] = f2[i] = 0;
		if (col[i]==1) f0[i] = 1;
		else if (col[i]==2) f1[i] = 1;
		else f2[i] = 1;
	}
	sort (p, p+len[3]+1, [](int a,int b) {
			return h[a]>h[b];
			});
//////////////////////////////////////////////////////////////////
	auto add = [](int &a,int b) {
		a += b; if (a<0) a+=mod; if (a>=mod) a-=mod;
	};
	auto mul = [](int x,int y,int z) {
		return 1ll*x*y%mod*z%mod;
	};
//////////////////////////////
	int mn = min (len[3]-len[2], min (len[2]-len[1], len[1]+1))-1;
	int T = 0;
	for (int i=mn, j=0; i>=1; i--) {
		while (h[p[j]] >= i) {
			int cur = sa[p[j]], lst = sa[p[j]-1];
			cur = dsu(cur), lst = dsu(lst);
			add (T, -mul (f0[cur], f1[cur], f2[cur]));
			add (T, -mul (f0[lst], f1[lst], f2[lst]));
			add (f0[cur], f0[lst]);
			add (f1[cur], f1[lst]);
			add (f2[cur], f2[lst]);
			f0[lst] = 0;
			f1[lst] = 0;
			f2[lst] = 0;
			add (T, mul (f0[cur], f1[cur], f2[cur]));
			fa[lst] = cur;
			j ++;
		}
		ans[i] = T;
	}
	for (int i=1; i<=mn; i++) printf ("%d ", ans[i]); puts ("");
	return 0;
}
