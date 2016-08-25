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

const int M = 50000+210;
int sa[M], rk[M], h[M], st[17][M];

void da (char *s,int n,int m) {
	static int t1[M], t2[M], c[M];
	int *x=t1, *y=t2, i,j,k,p=1;
	memset (c, 0, sizeof(c[0])*m);
	for (i=0; i<n; i++) c[x[i]=s[i]] ++;
	for (i=1; i<m; i++) c[i] += c[i-1];
	for (i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
	for (k=1; p<n; k<<=1, m=p) {
		for (p=0, i=n-k; i<n; i++) y[p++] = i;
		for (i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k;
		memset (c, 0, sizeof(c[0])*m);
		for (i=0; i<n; i++) c[x[i]] ++;
		for (i=1; i<m; i++) c[i] += c[i-1];
		for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
		for (swap(x,y), x[sa[0]]=0, p=i=1; i<n; i++)
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] &&
				y[sa[i]+k] == y[sa[i-1]+k] ? p-1 : p++;
	}
	memcpy (rk, x, sizeof(x[0])*n);
	for (i=0, k=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
	memcpy (st[0], h, sizeof(h[0])*n);
	for (k=1; 1<<k<=n; k++)
		for (i=0; i+(1<<k)-1<n; i++)
			st[k][i] = min (st[k-1][i], st[k-1][i+(1<<k-1)]);
}

char s[M];
int n, lens, szf;
pair<int,int> f[222];

int getlcp (int i,int j) {
	if (i==j) return lens-i;
	i = rk[i], j = rk[j];
	if (i>j) swap(i, j);
	i ++;
	int f = lg2(j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
}

int near (int i) {
	return lower_bound(f, f+szf, MP(i+1,-1))-f;
}

int left (int i) {
	return szf - (lower_bound(f, f+szf, MP(i+1,-1)) - f);
}

int ask (int i,int j) {
	if (i == j) return getlcp(i, j) + left(i);
	int ret = 0;
	int x[2] = {near(i), near(j)};
	while (1) {
		int lcp = getlcp(i, j);
		int tmp = min (lcp, min(f[x[0]].fi-i, f[x[1]].fi-j));
		ret += tmp, i += tmp, j += tmp;
		if (i<f[x[0]].fi && j<f[x[1]].fi) return ret;
		while (i == f[x[0]].fi && j == f[x[1]].fi) {
			if (f[x[0]].se == f[x[1]].se)
				ret++, x[0]++, x[1]++;
			else return ret;
		}
		while (j<f[x[1]].fi && i==f[x[0]].fi) {
			if (f[x[0]].se == s[j])
				ret++, x[0]++, j++;
			else return ret;
		}
		while (i<f[x[0]].fi && j==f[x[1]].fi) {
			if (s[i] == f[x[1]].se)
				ret++, i++, x[1]++;
			else return ret;
		}
	}
}

int main () {
	//freopen ("read.txt", "r", stdin);
	while (~ scanf ("%s", s)) {
		for (int i=0; i<222; i++) f[i] = MP(inf,-1);
		szf = 0;
		lens = strlen (s);
		scanf ("%d", &n);
		da (s, lens+1, 128);
		while (n --) {
			char t[10];
			int l, r;
			scanf ("%s", t);
			if (t[0]=='Q') {
				scanf ("%d%d", &l, &r);
				printf ("%d\n", ask (l-1, r-1));
			} else {
				scanf ("%s%d", t, &r);
				for (l=0, r--; l<szf; l++)
					if (f[l].fi>=r) break;
					else r--;
				if (r>lens+szf-1) r = lens+szf-1;
				for (int i=szf; i>l; i--) f[i] = f[i-1];
				f[l] = MP(r, t[0]);
				szf ++;
			}
		}
	}
	return 0;
}
