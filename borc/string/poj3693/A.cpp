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
char s[M];
int rk[M], sa[M], h[M], rk1[M], sa1[M], h1[M], n;
int st[18][M], st1[18][M];
pair<int,int> who[18][M];

void da (char *s, int *h,int *sa,int *rk,int st[][M],int n,int m) {
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
	for (i=0,k=0; i<n-1; h[rk[i++]] = k?k--:k)
		for (j=sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
	memcpy (st[0], h, sizeof(h[0])*n);
	for (k=1; 1<<k<=n; k++)
		for (i=0; i+(1<<k)-1<n; i++) 
			st[k][i] = min (st[k-1][i], st[k-1][i+(1<<k-1)]);
}

int getlcp (int st[][M],int *rk,int i,int j) {
	i = rk[i], j = rk[j];
	if (i>j) swap(i, j);
	i ++;
	int f = lg2 (j-i+1);
	return min (st[f][i], st[f][j-(1<<f)+1]);
} 

int getmins (int i,int j) {
	int f = lg2 (j-i+1);
	return who[f][i].fi<who[f][j-(1<<f)+1].fi?
		who[f][i].se : who[f][j-(1<<f)+1].se;
}

bool ismins (int i,int li,int j,int lj) {
	int lcp = getlcp(st, rk, i, j);
	if (lcp<li && lcp<lj) return s[i+lcp]<s[j+lcp];
	return li<lj;
}

int main () {
	//freopen ("read.txt", "r", stdin);
	int cas = 1;
	while (~scanf("%s", s) && s[0]!='#') {
		n = strlen(s);
		da (s, h, sa, rk, st, n+1, 128);
		reverse (s, s+n);
		da (s, h1, sa1, rk1, st1, n+1, 128);
		for (int i=0; i<n; i++) who[0][i] = MP(rk[i],i);
		for (int k=1; 1<<k<=n; k++)
			for (int i=0; i+(1<<k)-1<n; i++) {
				who[k][i].fi = 
					min(who[k-1][i].fi,who[k-1][i+(1<<k-1)].fi);
				who[k][i].se = who[k-1][i].fi == who[k][i].fi ?
					who[k-1][i].se : who[k-1][i+(1<<k-1)].se;
			}
		reverse (s, s+n);
		int beg=0, len=1, maxn=1;
		for (int i=0; i<n; i++) if (s[i]<s[beg]) beg = i;	
		for (int k=1; k<=n; k++) {
			for (int i=0; i+k<n; i+=k) {
				int revlcp = getlcp (st1, rk1, n-1-i-k, n-1-i);
				if (revlcp>k) continue;
				if (revlcp==0) revlcp ++;
				int lcp = getlcp (st, rk, i, i+k);
				int loop = (lcp+revlcp+k-1)/k;
				int l = i-revlcp+1;
				int r = l+(lcp+revlcp+k-1)%k;
				int _i = getmins (l, r);
				if (loop>maxn) {
					maxn = loop, beg = _i, len = loop*k;
				} else if (loop==maxn&&ismins(_i,loop*k,beg,len)) {
					beg = _i, len = loop*k;
				}
			}
		}
		s[beg+len] = '\0';
		printf ("Case %d: %s\n", cas++, s+beg);
	}
	return 0;
}
